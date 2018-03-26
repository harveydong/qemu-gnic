
#include "qemu/osdep.h"
#include "net/tap.h"
#include "qemu/range.h"
#include "hw/pci/msi.h"
#include "hw/pci/msix.h"
#include "net_tx_pkt.h"
#include "net_rx_pkt.h"



#include "hw/pci/pci.h"
#include "sysemu/dma.h"
#include "qemu/timer.h"
#include "net/net.h"
#include "net/eth.h"
#include "sysemu/sysemu.h"
#include "qemu/iov.h"

#include "hw/net/zxiw_regs.h"
#include "hw/net/zxiw_common.h"

#define	TYPE_ZXIW "zxiw"
#define	ZXIW_PCI_REVID	0x01
#define	ZXIW_MMIO_SIZE	0x800	
#define	ZXIW_MMIO_IDX	1
#define	ZXIW_MSIX_IDX	3

#define	ZXIW_MSIX_SIZE 8*1024
#define	ZXIW_MSIX_TABLE_OFFSET (0x0000)
#define	ZXIW_MSIX_PBA_OFFSET	(0x1000)
#define	ZXIW_MSIX_VEC_NUM 8
#define ZXIW_BUFFS_PER_DESC 256
#define	ZXIW_TX_NUM_QUEUES	1
#define	ZXIW_RX_NUM_QUEUES	1
#define ZXIW_MAX_TX_FRAGS	4
#define ZXIW_EEPROM_SIZE     2*1024

typedef struct EEpromat93c46d {
/*CSR00-CSR05*/
	uint8_t mac_address[6];
/*CSR085,0X6C*/
	uint8_t mii_polling_setting;
	uint8_t sub_sid[2];
	uint8_t	sub_vid[2];
	uint8_t devid[2];
	uint8_t pmcc;
	uint8_t data_sel;
	uint8_t pmu_data_reg;
	uint8_t auxcurr;
	uint8_t mcfg[2];
	uint8_t min_gnt;
	uint8_t max_lat;
	uint8_t dcfg[2];
	uint8_t cfga_d[4];
	uint8_t chksum;
	
}EEpromat93c46d;

enum ZXIWallcounters {
	rxallpkts = 0,
	 rxokpkts, 
	 txokpkts, 
	 rxerrorpkts,
	 rxruntokpkt,
	 rxrunterrpkt,
	 rx64pkts,
	 tx64pkts,
	 rx65to127pkts,
	 tx65to127pkts,
	 rx128to255pkts, 
	 tx128to255pkts, 
	 rx256to511pkts,
	 tx256to511pkts,
	 rx512to1023pkts,	
	 tx512to1023pkts,	
	 rx1024to1518pkts,
	tx1024to1518pkts,

	 txethercollisions,
	 rxpktcrce,
	rxjumbopkts,
	 txjumbopkts,
	 rxmaccontrolframes,
	 txmaccontrolframes,
	 rxpktfae,
	 rxlongokpkt,
	 rxlongpkterrpkt,
	 txsqeerrors,
	 rxnobuf,
	 rxsymbolerrors,
	 inrangelentherrors,
	 latecollisions

};

typedef struct zxiw_tx_props {
	uint8_t ipcss;
	uint8_t paylen;

}zxiw_tx_props;

typedef struct zxiw_rx_props{
	uint8_t rx_rss;
	uint8_t checksum;
}zxiw_rx_props;

static uint8_t mac_init_default[ZXIW_MAC_SIZE] = {



	[0x08] = 0x02,
	[0x09] = 0x02,
	[0xc] = 0x02,
	[0xd] = 0x02,
	[0x6d] = 0x80,
	[0x6e] = 0x10,
	[0x71] = 0x01,
	[0x78] = 0x10,
	[0x7a] = 0x10,
	[0x7f] = 0x7f,
	[0x82] = 0x10,
	[0x84] = 0x08,
	[0x86] = 0x10,
	[0x90] = 0x80,
	[0x97] = 0x80,
	[0x99] = 0xa0,
	[0xa3] = 0x02,
	[0xa7] = 0x02,
	[0x1b0] = 0x6d,
	[0x1b1] = 0x5a,
	[0x1b2] = 0x56,
	[0x1b3] = 0xda,
	[0x1b4] = 0x25,
	[0x1b5] = 0x5b,
	[0x1b6] = 0x0e,[0x1b7] = 0xc2,\
	[0x1b8] = 0x41,[0x1b9] = 0x67,[0x1ba] = 0x25,[0x1bb] = 0x3d,\
	[0x1bc] = 0x43,[0x1bd] = 0xa3,[0x1be] = 0x8f,[0x1bf] = 0xb0,\
	[0x1c0] = 0xd0,[0x1c1] = 0xca,[0x1c2] = 0x2b,[0x1c3] = 0xcb,\
	[0x1c4] = 0xae,[0x1c5] = 0x7b,[0x1c6] = 0x30,[0x1c7] = 0xb4,\
	[0x1c8] = 0x77,[0x1c9] = 0xcb,[0x1ca] = 0x2d,[0x1cb] = 0xa3,\
	[0x1cc] = 0x80,[0x1cd] = 0x30,[0x1ce] = 0xf2,[0x1cf] = 0x0c,\
	[0x1d0] = 0x6a,[0x1d1] = 0x42,[0x1d2] = 0xb7,[0x1d3] = 0x3b,\
	[0x1d4] = 0xbe,[0x1d5] = 0xac,[0x1d6] = 0x01,[0x1d7] = 0xfa,\

	[0x1eb] = 0x04,[0x236] = 0x04,[0x237] = 0x04,[0x5d0] = 0x01,\
	[0x5d9] = 0x01,[0x5e0] = 0x44,[0x5e4] = 0xff,[0x5e8] = 0xff
};


static const uint16_t zxiw_phy_reg_init[] = {
	[PHY_CTRL] = MII_CR_SPEED_SELECT_MSB | MII_CR_FULL_DUPLEX | MII_CR_AUTO_NEG_EN,
	[PHY_STATUS] = MII_SR_EXTENDED_CAPS |MII_SR_LINK_STATUS|MII_SR_AUTONEG_CAPS |MII_SR_EXTENDED_STATUS |MII_SR_UD_ABILITY  |\
                       MII_SR_10T_HD_CAPS       |\
                       MII_SR_10T_FD_CAPS       |\
                       MII_SR_100X_HD_CAPS      |\
                       MII_SR_100X_FD_CAPS,
    [PHY_ID1]               = 0x001C,
    [PHY_ID2]               = 0xC916,
    [PHY_AUTONEG_ADV]       = 0x01e1,
    [PHY_LP_ABILITY]        = 0x0000,
    [PHY_AUTONEG_EXP]       = 0x0064,
	[PHY_NEXT_PAGE_TX]      = 0X2001,
	[PHY_1000T_CTRL]        = 0x0200,
	[PHY_1000T_STATUS]      = 0x3c00,
	
};



typedef struct ZXIWCore{
	uint8_t mac[ZXIW_MAC_SIZE];
	//uint8_t mac_default[ZXIW_MAC_SIZE];
	
	uint16_t phy[ZXIW_PHY_SIZE];
	uint16_t phy_default[ZXIW_PHY_SIZE];

	EEpromat93c46d eeprom;
	enum ZXIWallcounters all_counters[0x100];

	uint32_t rx_desc_buf_size;
	uint8_t rx_desc_len;

			
	QEMUTimer *autoneg_timer;
	QEMUTimer *timer0;
	QEMUTimer *timer1;
	
	struct zxiw_tx{
		zxiw_tx_props props;
		struct NetTxPkt *tx_pkt;
		uint32_t tx_desc_base_hi,tx_desc_addr_hi;
		uint32_t tx_desc_base_lo,tx_desc_addr_lo;
		uint16_t tdindex;
		uint16_t tdcsize;

	}tx[ZXIW_TX_NUM_QUEUES];

	struct zxiw_rx{
		zxiw_rx_props props;
		struct NetRxPkt *rx_pkt;
	}rx[ZXIW_RX_NUM_QUEUES];

	int max_queue_num;
	VMChangeStateEntry *vmstate;
	
	uint8_t permanent_mac[ETH_ALEN];
	NICState *owner_nic;
	PCIDevice *owner;
	void (*owner_start_recv)(PCIDevice *d);
	
}ZXIWCore;




typedef struct ZXIWState {
	PCIDevice parent_obj;
	
	NICConf	conf;	
	NICState *nic;
	
	//ZXIWallcounters all_counters;
	
	MemoryRegion msix;
	MemoryRegion mmio;
	
	uint16_t subsys_ven;
	uint16_t subsys;
	uint16_t subsys_ven_used;
	uint16_t subsys_used;

	ZXIWCore core;	
		

}ZXIWState;

#define	ZXIW(obj) OBJECT_CHECK(ZXIWState,(obj),TYPE_ZXIW)


static inline void zxiw_update_regs_on_link_down(uint8_t *mac,uint16_t *phy)
{
	mac[PHYSR0] &= ~ZXIW_STATUS_LINK;
	phy[PHY_STATUS] &= ~MII_SR_LINK_STATUS;
	phy[PHY_STATUS] &= ~MII_SR_AUTONEG_COMPLETE;
	phy[PHY_LP_ABILITY] &= ~MII_LPAR_LPACK;
}
static inline void zxiw_update_regs_on_link_up(uint8_t *mac,uint16_t *phy)
{
	mac[PHYSR0] |= ZXIW_STATUS_LINK;
	phy[PHY_STATUS] |= MII_SR_LINK_STATUS;
}

static uint64_t zxiw_hw_hib_read(ZXIWCore *core,hwaddr addr,unsigned size)
{
	
	 core->mac[MIBCR] &= ~MIBCR_MIBCLR ;
	return core->mac[MIBCR];	

}


static uint64_t zxiw_core_read(ZXIWCore *core,hwaddr addr,unsigned size)
{
	uint64_t val = 0;
//	uint16_t index = zxiw_get_reg_index_with_offset();

	printf("mmio read addr is 0x%lx,and size is %d\n",addr,size);
	if(addr == 0x84)
		return zxiw_hw_hib_read(core,addr,size);
	switch(size){
	case 1:
		val = core->mac[addr];
		break;
	case 2:
		val = (core->mac[addr + 1]) << 8 | core->mac[addr];
		break;
	case 4:
		val =(core->mac[addr + 3]) << 24 |(core->mac[addr + 2]) << 16| (core->mac[addr + 1]) << 8 | core->mac[addr];
		break;

	default:
		printf("error mmio read size %d\n",size);
		

	}
	return val;
}

static uint64_t zxiw_mmio_read(void *opaque,hwaddr addr,unsigned size)
{
	ZXIWState *s = opaque;
	return zxiw_core_read(&s->core,addr,size);
}


static void zxiw_core_write(ZXIWCore *core,hwaddr addr,uint64_t val,unsigned size)
{

	printf("mmio write addr 0x%lx,and val is 0x%lx,and size is %d\n",addr,val,size);
	switch(size){
	case 1:
		core->mac[addr] = (uint8_t)val;
		break;
	case 2:
		core->mac[addr] = (uint8_t)val;
		core->mac[addr+1] = (uint8_t)(val >> 8);
		break;
	case 4:
		core->mac[addr] = (uint8_t)val;
		core->mac[addr+1] = (uint8_t)(val >> 8);
		core->mac[addr + 2] = (uint8_t)(val >> 16);
		core->mac[addr + 3]= (uint8_t)(val >> 24);
		break;
	default:
		printf("mmio write size %d is error \n",size);
	}
}


static void zxiw_mmio_write(void *opaque,hwaddr addr,uint64_t val,unsigned size)
{
	ZXIWState *s = opaque;
	zxiw_core_write(&s->core,addr,val,size);
}

static const MemoryRegionOps zxiw_mmio_ops = {

	.read = zxiw_mmio_read,
	.write = zxiw_mmio_write,
	.endianness = DEVICE_LITTLE_ENDIAN,
	.impl = {
		.min_access_size = 1,
		.max_access_size = 4,
	},

};

static void zxiw_unuse_msix_vectors(ZXIWState *s,int num_vectors)
{
	int i;
	
	for(i = 0; i < num_vectors;i++){
		msix_vector_unuse(PCI_DEVICE(s),i);
	}
}

static bool zxiw_use_msix_vectors(ZXIWState *s,int num_vectors)
{
	int i;

	printf("use msix vectors is %d\n",num_vectors);	
	for(i = 0; i < num_vectors;i++){
		int res = msix_vector_use(PCI_DEVICE(s),i);
		if(res < 0){
			printf("use msix vectors %d failed\n",i);
			zxiw_unuse_msix_vectors(s,i);
			return false;
		}
	}

	return true;

}


static void zxiw_init_msix(ZXIWState *s)
{
	PCIDevice *d = PCI_DEVICE(s);
	int res;

	res = msix_init(PCI_DEVICE(s),ZXIW_MSIX_VEC_NUM,&s->msix,ZXIW_MSIX_IDX,ZXIW_MSIX_TABLE_OFFSET,&s->msix,ZXIW_MSIX_IDX,ZXIW_MSIX_PBA_OFFSET,0xE0,NULL);
	
	if(res < 0)
	{
		printf("init msix failed\n");
	}else{
		if(!zxiw_use_msix_vectors(s,ZXIW_MSIX_VEC_NUM)){
			msix_uninit(d,&s->msix,&s->msix);
		}

	}


}

static void zxiw_cleanup_msix(ZXIWState *s)
{
	if(msix_present(PCI_DEVICE(s))){
		zxiw_unuse_msix_vectors(s,ZXIW_MSIX_VEC_NUM);
		msix_uninit(PCI_DEVICE(s),&s->msix,&s->msix);
	}
}


static int zxiw_can_receive(NetClientState *nc)
{
	
	printf("zxiw_can_receive here\n");
	return 1;
}

static ssize_t zxiw_receive(NetClientState *nc,const uint8_t *buf,size_t size)
{

	printf("ziw_receive here\n");
	return size;
}

static void zxiw_link_status_change(NetClientState *nc)
{

	printf("zxiw_link_status change here\n");
}

static NetClientInfo net_zxiw_info = {
	.type = NET_CLIENT_DRIVER_NIC,
	.size = sizeof(NICState),
	.can_receive = zxiw_can_receive,
	.receive = zxiw_receive,
	.link_status_changed = zxiw_link_status_change
};

static void zxiw_init_net_peer(ZXIWState *s,PCIDevice *pdev,uint8_t *macaddr)
{

	DeviceState *dev = DEVICE(pdev);
//	NetClientState *nc;
//	int i;

//	s->conf.peers.queues = 8;
	s->nic = qemu_new_nic(&net_zxiw_info,&s->conf,object_get_typename(OBJECT(s)),dev->id,s);

	printf("init net peer queue is %d\n",s->conf.peers.queues);
	
	s->core.max_queue_num = s->conf.peers.queues - 1;

	memcpy(s->core.permanent_mac,macaddr,sizeof(s->core.permanent_mac));

	qemu_format_nic_info_str(qemu_get_queue(s->nic),macaddr);
	return;
	

}


static void zxiw_core_realize(ZXIWState *s)
{
	s->core.owner = &s->parent_obj;
	s->core.owner_nic = s->nic;
}

static const uint8_t zxiw_eeprom_template[] = {
	0x00,0x02,0x02a,0xe0,0x43,0x0d,0x00,0x00,0x10,0x01,0x06,0x11,0x80,0x91,0x17,0x1d,0x1f,0x00,0x00,0x80,0x00,0x01,0x00,0x00,0x00,0x00,0x03,0x10,0x00,0x00,0x74,0x11,0x00,0x00,0x00,0xff,0x0a,0x00,0x00,0x00,

};

static void zxiw_core_prepare_eeprom(EEpromat93c46d *eeprom,const uint8_t *templ,uint32_t templ_size,uint16_t dev_id,const uint8_t *macaddr)
{

	int i;

	memmove(eeprom,templ,templ_size);
	for(i = 0; i < 6;i++)
		eeprom->mac_address[i] = macaddr[i];



}

static void zxiw_update_regs_on_autoneg_done(uint8_t *mac,uint16_t *phy)
{
	printf("update regs on autoneg done\n");
	zxiw_update_regs_on_link_up(mac,phy);
	phy[PHY_LP_ABILITY] |= MII_LPAR_LPACK;
	phy[PHY_STATUS] |= MII_SR_AUTONEG_COMPLETE;
	

}
static inline bool zxiw_have_autoneg(ZXIWCore *core)
{
	return core->phy[PHY_CTRL] & MII_CR_AUTO_NEG_EN;
}


static void zxiw_update_flowctl_status(ZXIWCore *core)
{
	if(zxiw_have_autoneg(core) && core->phy[PHY_STATUS] & MII_SR_AUTONEG_COMPLETE){
		core->mac[CR2_SET] |=ZXIW_CTRL_XONEN | ZXIW_CTRL_TFCE | ZXIW_CTRL_RFCE;
	}else{
		return ;
	}
}

void zxiw_start_recv(ZXIWCore *core)
{

	int i;
	
	for(i = 0; i <= core->max_queue_num;i++)
		qemu_flush_queued_packets(qemu_get_subqueue(core->onwer_nic,i));
}


static void zxiw_set_interrupt_cause(ZXIWCore *core,uint32_t val)
{
	core->mac[] = val;
}

static inline void zxiw_autoneg_timer(void *opaque)
{
	ZXIWCore *core = opaque;

	printf("zxiw autoneg timer here\n");	
	if(!qemu_get_queue(core->owner_nic)->link_down){
		zxiw_update_regs_on_autoneg_done(core->mac,core->phy);	
		zxiw_start_recv(core);
		zxiw_update_flowctl_status(core);
		zxiw_set_interrupt_cause(core,ZXIW_INTCAUSE_LSC);
	}
}

static const VMStateDescription zxiw_vmstate_tx = {
	.name = "zxiw-tx",
	.version_id = 1,
	.minimum_version_id = 1,
	.fields = (VMStateField[]){
		VMSTATE_UINT8(props.paylen,struct zxiw_tx),
		VMSTATE_END_OF_LIST()
	
	}

};

static const VMStateDescription zxiw_vmstate_rx = {

	.name = "zxiw-rx",
	.version_id = 1,
	.minimum_version_id = 1,
	.fields = (VMStateField[]){

		VMSTATE_UINT8(props.checksum,struct zxiw_rx),
		VMSTATE_END_OF_LIST()

	}

};

static void zxiw_core_pre_save(ZXIWCore *core)
{
	int i;
	NetClientState *nc = qemu_get_queue(core->owner_nic);
	
	if(nc->link_down && zxiw_have_autoneg(core)){
		core->phy[PHY_STATUS] |= MII_SR_AUTONEG_COMPLETE;
		zxiw_update_flowctl_status(core);
	}

	for(i = 0; i < ARRAY_SIZE(core->tx); i++){

		;
	}

}

static int zxiw_core_post_load(ZXIWCore *core)
{
	NetClientState *nc = qemu_get_queue(core->owner_nic);
	nc->link_down = (core->mac[PHYSR0] & ZXIW_STATUS_LINK) == 0;

	return 0;
}
static int zxiw_post_load(void *opaque,int version_id)
{
	ZXIWState *s = opaque;
	
	if((s->subsys != s->subsys_used) || (s->subsys_ven != s->subsys_ven_used)){

	printf("error: cannot migrate while device properties\n");
	return -1;
	}

	return zxiw_core_post_load(&s->core);
}

static void zxiw_pre_save(void *opaque)
{
	ZXIWState *s = opaque;
	
	zxiw_core_pre_save(&s->core);

}


static const VMStateDescription zxiw_vmstate = {
	.name = "zxiw",
	.version_id = 1,
	.minimum_version_id = 1,
	.pre_save = zxiw_pre_save,
	.post_load = zxiw_post_load,
	.fields = (VMStateField[]){
		VMSTATE_PCI_DEVICE(parent_obj,ZXIWState),
		VMSTATE_MSIX(parent_obj,ZXIWState),
		VMSTATE_UINT8(core.rx_desc_len,ZXIWState),
		VMSTATE_UINT32(core.rx_desc_buf_size,ZXIWState),
		VMSTATE_UINT16_ARRAY(core.phy,ZXIWState,ZXIW_PHY_SIZE),
		//VMSTATE_UINT16(core.eeprom,ZXIWState,ZXIW_EEPROM_SIZE),
		VMSTATE_UINT8_ARRAY(core.mac,ZXIWState,ZXIW_MAC_SIZE),
		VMSTATE_UINT8_ARRAY(core.permanent_mac,ZXIWState,ETH_ALEN),
		VMSTATE_UINT16(subsys,ZXIWState),
		VMSTATE_UINT16(subsys_ven,ZXIWState),
		VMSTATE_STRUCT_ARRAY(core.tx,ZXIWState,ZXIW_TX_NUM_QUEUES,0,zxiw_vmstate_tx,struct zxiw_tx),
		VMSTATE_STRUCT_ARRAY(core.rx,ZXIWState,ZXIW_RX_NUM_QUEUES,0,zxiw_vmstate_rx,struct zxiw_rx),
		VMSTATE_END_OF_LIST()
	}

};

static void zxiw_autoneg_resume(ZXIWCore *core)
{
	if(zxiw_have_autoneg(core) && !(core->phy[PHY_STATUS] & MII_SR_AUTONEG_COMPLETE)){
		qemu_get_queue(core->owner_nic)->link_down = false;
		timer_mod(core->autoneg_timer,qemu_clock_get_ms(QEMU_CLOCK_VIRTUAL) + 500);
	}

}

static inline void zxiw_autoneg_pause(ZXIWCore *core)
{

	timer_del(core->autoneg_timer);
}

static void zxiw_vm_state_change(void *opaque,int running,RunState state)
{
	ZXIWCore *core = opaque;
	if(running){
	//	zxiw_intrmgr_resume(core);
		zxiw_autoneg_resume(core);
	}else{
		zxiw_autoneg_pause(core);
	//	zxiw_intrmgr_pause(core);
	}
}


static void zxiw_core_pci_realize(ZXIWCore *core, const uint8_t *eeprom_templ,uint32_t eeprom_size,const uint8_t *macaddr)
{
	int i;

	core->autoneg_timer = timer_new_ms(QEMU_CLOCK_VIRTUAL,zxiw_autoneg_timer,core);

	core->vmstate = qemu_add_vm_change_state_handler(zxiw_vm_state_change,core);
	for(i = 0; i < ZXIW_TX_NUM_QUEUES;i++)
		net_tx_pkt_init(&core->tx[i].tx_pkt,core->owner,ZXIW_MAX_TX_FRAGS,false);

	for(i = 0; i < ZXIW_RX_NUM_QUEUES;i++)
		net_rx_pkt_init(&core->rx[i].rx_pkt,false);

	zxiw_core_prepare_eeprom(&core->eeprom,eeprom_templ,eeprom_size,PCI_DEVICE_GET_CLASS(core->owner)->device_id,macaddr);

		

}

static void zxiw_write_config(PCIDevice *pdev,uint32_t address,uint32_t val,int len)
{
	//ZXIWState *s = ZXIW(pdev);
	
	printf("zxiw_write_config here\n");

	pci_default_write_config(pdev,address,val,len);
	
	if(range_covers_byte(address,len,PCI_COMMAND) && (pdev->config[PCI_COMMAND] & PCI_COMMAND_MASTER)){
		;//zxiw_start_recv(&s->core);
	}
}

static int zxiw_add_pm_capability(PCIDevice *pdev,uint8_t offset,uint16_t pmc)
{
	Error *local_err = NULL;
	int ret = pci_add_capability(pdev,PCI_CAP_ID_PM,offset,PCI_PM_SIZEOF,&local_err);
	if(local_err){
		printf("error add pm\n");
		return ret;
	}

	pci_set_word(pdev->config + offset + PCI_PM_PMC,PCI_PM_CAP_VER_1_1|pmc);
	pci_set_word(pdev->wmask + offset + PCI_PM_CTRL,PCI_PM_CTRL_STATE_MASK|PCI_PM_CTRL_PME_ENABLE|PCI_PM_CTRL_DATA_SEL_MASK);
	pci_set_word(pdev->w1cmask +offset +PCI_PM_CTRL,PCI_PM_CTRL_PME_STATUS);
	return ret;
}
static void pci_zxiw_realize(PCIDevice *pdev,Error **errp)
{
	ZXIWState *s = ZXIW(pdev);
	uint8_t *macaddr;
	//int ret;
	int i;
	static const uint16_t zxiw_pm_offset = 0x50;

	printf("into zxiw realize,and queue number is %d\n\n",s->conf.peers.queues);
	pdev->config_write = zxiw_write_config;
	pdev->config[PCI_INTERRUPT_PIN] = 1;
	
	pci_set_word(pdev->config + PCI_SUBSYSTEM_VENDOR_ID,s->subsys_ven);
	pci_set_word(pdev->config + PCI_SUBSYSTEM_ID,s->subsys);
	s->subsys_ven_used = s->subsys_ven;
	
	s->subsys_used = s->subsys;
	printf("zxiw realized and subsys_ven is 0x%x,and subsys is 0x%x\n",s->subsys_ven,s->subsys);
	memory_region_init_io(&s->mmio,OBJECT(s),&zxiw_mmio_ops,s,"zxiw-mmio",ZXIW_MMIO_SIZE);	

	pci_register_bar(pdev,ZXIW_MMIO_IDX,PCI_BASE_ADDRESS_SPACE_MEMORY,&s->mmio);
	memory_region_init(&s->msix,OBJECT(s),"zxiw-msix",ZXIW_MSIX_SIZE);
	pci_register_bar(pdev,ZXIW_MSIX_IDX,PCI_BASE_ADDRESS_SPACE_MEMORY,&s->msix);

	qemu_macaddr_default_if_unset(&s->conf.macaddr);
	macaddr = s->conf.macaddr.a;

	zxiw_init_msix(s);

	if(zxiw_add_pm_capability(pdev,zxiw_pm_offset,PCI_PM_CAP_DSI) < 0)
	{
		printf("failed to initialize PM capability\n");
	}	
	
	for(i = 0; i < ZXIW_MAC_SIZE; i++)
		s->core.mac[i] = mac_init_default[i];


	
	zxiw_init_net_peer(s,pdev,macaddr);

	zxiw_core_realize(s);
	zxiw_core_pci_realize(&s->core,zxiw_eeprom_template,sizeof(zxiw_eeprom_template),macaddr);
	printf("zxiw here is realize\n");
}

static void zxiw_core_pci_uninit(ZXIWCore *core)
{
	int i;

	qemu_del_vm_change_state_handler(core->vmstate);
	for(i = 0; i < ZXIW_TX_NUM_QUEUES;i++)
	{
		net_tx_pkt_reset(core->tx[i].tx_pkt);
		net_tx_pkt_uninit(core->tx[i].tx_pkt);
	}	

	for(i = 0; i < ZXIW_RX_NUM_QUEUES;i++)
	{
		net_rx_pkt_uninit(core->rx[i].rx_pkt);
	}

}
static void pci_zxiw_uninit(PCIDevice *pdev)
{
	ZXIWState *s = ZXIW(pdev);
	
	zxiw_core_pci_uninit(&s->core);
	qemu_del_nic(s->nic);
	
	zxiw_cleanup_msix(s);
	msi_uninit(pdev);
	printf("zxiw uninit\n");
}



static inline void zxiw_link_down(ZXIWCore *core)
{
	zxiw_update_regs_on_link_down(core->mac,core->phy);
	zxiw_update_flowctl_status(core);

}

static void zxiw_reset_mac_addr(NICState *nic,uint8_t *mac_regs,uint8_t *mac_addr)
{
	int i;
	
	for(i = 0; i < 6; i++)
	{
		mac_regs[MAC + i] = mac_addr[i];
		
	}

}



#if 0 
static const uint8_t zxiw_mac_reg_init[] = {
	[MAC]=0x00,
	[MAC+1]=0x02,
	[MAC+2]=0x2a,
	[MAC+3] = 0xe0,
	[NODE_CTRL]=0x42,
	[NODE_CTRL+1]	= 0xfb,
	[MIICFG] =  0x1E,
	[MCFG0 ]=0x00,
	[MCFG1] = 0x01,
	[CFGA]= 0X03,
	[CFGB]= 0x10,
	[CFGC]= 0x00,
	[CFGD] = 0x00,
	[EECHKSUM] = 0x74,
	
	
	
	
};

#endif

static void zxiw_reset_mac_phy_default(ZXIWCore *core)
{

	memset(core->phy,0,sizeof(core->phy));
	memmove(core->phy,zxiw_phy_reg_init,sizeof(zxiw_phy_reg_init));
	memset(core->mac,0,sizeof(core->mac));
	memmove(core->mac,mac_init_default,sizeof(mac_init_default));

}


static void zxiw_core_reset(ZXIWCore *core)
{
	int i;


	timer_del(core->autoneg_timer);
	
	zxiw_reset_mac_phy_default(core);
	
	if(qemu_get_queue(core->owner_nic)->link_down){
		zxiw_link_down(core);
	}

	zxiw_reset_mac_addr(core->owner_nic,core->mac,core->permanent_mac);

	for(i = 0; i < ARRAY_SIZE(core->tx);i++){
		net_tx_pkt_reset(core->tx[i].tx_pkt);
		memset(&core->tx[i].props,0,sizeof(core->tx[i].props));
		
	}
#if 0
	for(i = 0; i < ARRAY_SIZE(core->rx);i++)
	{
		memset(&core->rx[i].props,0,sizeof(core->rx[i].props));
	}

#endif

}

static void zxiw_reset(DeviceState *d)
{
	ZXIWState *s = ZXIW(d);
	zxiw_core_reset(&s->core);
	printf("zxiw reset here\n");
}

static void zxiw_instance_init(Object *obj)
{
	//ZXIWState *s = ZXIW(obj);

	printf("here is zxiw_instance_init\n"); 

}

static PropertyInfo zxiw_prop_subsys_ven,zxiw_prop_subsys;//,zxiw_prop_peers_queues;


static Property zxiw_properties[] = {
	DEFINE_NIC_PROPERTIES(ZXIWState,conf),
	DEFINE_PROP_SIGNED("subsys_ven",ZXIWState,subsys_ven,0x1106,zxiw_prop_subsys_ven,uint16_t),
	DEFINE_PROP_SIGNED("subsys",ZXIWState,subsys,0x0130,zxiw_prop_subsys,uint16_t),
	
//	DEFINE_PROP_INT32("queue",ZXIWState,conf.peers.queues,8),
	DEFINE_PROP_END_OF_LIST(),

};

static void zxiw_class_init(ObjectClass *kclass,void *data)
{
	DeviceClass *dc = DEVICE_CLASS(kclass);
	PCIDeviceClass *k = PCI_DEVICE_CLASS(kclass);

	k->realize = pci_zxiw_realize;
	k->exit = pci_zxiw_uninit;
	//k->romfile = "efi-zxiw.rom";	
	k->vendor_id = PCI_VENDOR_ID_ZX;
	k->device_id = PCI_DEVICE_ID_ZX_IW;
	k->revision = ZXIW_PCI_REVID; 
	k->class_id = PCI_CLASS_NETWORK_ETHERNET;
	k->is_express	= 1;
	
	dc->desc = "ZhaoXin Gigabit iwarp controller";
	
	dc->reset = zxiw_reset;
	dc->props = zxiw_properties;
	
	zxiw_prop_subsys_ven = qdev_prop_uint16;
	zxiw_prop_subsys = qdev_prop_uint16;
	set_bit(DEVICE_CATEGORY_NETWORK,dc->categories);

}


static const TypeInfo zxiw_info = {
	.name = TYPE_ZXIW,
	.parent = TYPE_PCI_DEVICE,
	.instance_size = sizeof(ZXIWState),
	.class_init = zxiw_class_init,
	.instance_init = zxiw_instance_init,
	
};

static void zxiw_register_type(void)
{

	type_register_static(&zxiw_info);
}

type_init(zxiw_register_type)
