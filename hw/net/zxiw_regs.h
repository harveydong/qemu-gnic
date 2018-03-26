/*******************************************************************************

  ZhaoXin RDMA  Linux driver
  Copyright(c) 1999 - 2017 zhaoxin Corporation.

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, see <http://www.gnu.org/licenses/>.

  The full GNU General Public License is included in this distribution in
*******************************************************************************/

/* zxgb_mac.h
 * Structures, enums, and macros for the MAC
 */

#ifndef HW_ZXIW_REGS_H
#define HW_ZXIW_REGS_H


#define ZXIW_MAC_SIZE 0x800
#define	ZXIW_PHY_SIZE	0x90

/*all register default value,bit is 32*/


/*Transimt and Receive Control Register bits*/
#define	TRC_SEP	(1<<0)
#define	TRC_AR	(1<<1)
#define	TRC_AM	(1<<2)
#define	TRC_AB	(1<<3)
#define	TRC_PROM (1 << 4)
#define	TRC_AL (1 << 5)
#define	TRC_AP (1 << 6)
#define	TRC_AS (1<< 7)


#define	TRC_LB	(3 << 0)
#define	TRC_COLTMC (3 << 2)


/*Global Command Register bit*/
#define CR0_STRT (1 << 0)
#define	CR0_STOP ( 1 << 1)
#define	CR0_RXON (1 << 2)
#define	CR0_TXON (1 << 3)


#define	CR1_DISAU ( 1 << 0)
#define	CR1_JBO_SP (1 << 1)
#define	CR1_MDISAB (1 << 2)
#define	CR1_TM0EN (1 << 5)
#define	CR1_TM1EN (1 << 6)
#define	CR1_SFRST (1 << 7)


#define	 CR2_XLITH (3 << 0)
#define	CR2_XHITH (3 << 2)
#define	 CR2_HDXFCEN (1 << 4)
#define CR2_FDXRFCEN (1 << 5)
#define	CR2_FDXTFCEN (1 << 6)
#define CR2_XONEN (1 << 7)


#define CR3_DIAG (1 << 4)

#define GCR_0123_DEFAULT 0x00000202

/*Global Command Register Clear Register bit*/
#define CR0C_STRT (1 << 0)
#define	CR0C_STOP ( 1 << 1)
#define	CR0C_RXON (1 << 2)
#define	CR0C_TXON (1 << 3)


#define	CR1C_DISAU ( 1 << 0)
#define	CR1C_JBO_SP (1 << 1)
#define	CR1C_MDISAB (1 << 2)
#define	CR1C_TM0EN (1 << 5)
#define	CR1C_TM1EN (1 << 6)
#define	CR1C_SFRST (1 << 7)


#define	 CR2C_XLITH (3 << 0)
#define	CR2C_XHITH (3 << 2)
#define	 CR2C_HDXFCEN (1 << 4)
#define CR2C_FDXRFCEN (1 << 5)
#define	CR2C_FDXTFCEN (1 << 6)
#define CR2C_XONEN (1 << 7)


#define CR3C_DIAG (1 << 4)


/*Interrupt Control Reigster*/
#define	ICR_SCRELOAD (1 << 0)
#define	ICR_HCRELOAD (1 << 1)
#define	ICR_INTPENDING (1 << 2)
#define	ICR_PMSK (3 << 3)
#define ICR_RSUPPDIS (1 << 5)
#define ICR_TSUPPDIS (1 << 6)
#define ICR_UDPINTS (1 << 7)

#define ICR_TDSTR (1 << 0)
#define ICR_TDRBS (1 << 1)
#define ICR_TDWBS (1 << 2)
#define ICR_TFDBS ( 1 << 3)

#define ICR_RDSTR0 (1 << 0)
#define ICR_RDRBS0 ( 1 << 1)
#define ICR_RDWBS0 (1 << 2)
#define ICR_RFDBS0 ( 1 << 3)

/*Interrupt Status Register bit (ISR0,ISR1,ISR2,ISR3)*/
#define ISR_PPRX0I (1 << 0)
#define ISR_PPTXI ( 1 << 1)
#define ISR_PXR0I (1 << 2)
#define ISR_PTXI (1 << 3)
#define ISR_PTXnI ( 0XF << 4)

#define ISR_PRXI ( 1 << 0)
#define ISR_RCABT (1 << 1)
#define ISR_RACEI (1 << 2)
#define ISR_FLONI (1 << 3)
#define ISR_OVFI (1 << 4)
#define ISR_LSTE0I ( 1 << 5)
#define ISR_LSTPE0I ( 1 << 6)
#define ISR_SRCI (1 << 7)

#define ISR_TMR0I ( 1 << 0)
#define ISR_TMR1I ( 1 << 1)
#define ISR_PWEI (1 << 2)
#define ISR_PHYI (1 << 3)
#define ISR_SHDNII (1 << 4)
#define ISR_MIBFI (1 << 5)
#define ISR_UDPI ( 1 << 6)

#define ISR_RXSTL0I (1 << 0)
#define ISR_TXSTLI (1 << 1)

/*Interrupt Enable Register(mask) bit (IMR0,IMR1,IMR2,IMR3)*/
#define IMR0_PPRX0I (1 << 0)
#define IMR0_PPTXI ( 1 << 1)
#define IMR0_PXR0I (1 << 2)
#define IMR0_PTXI (1 << 3)
#define IMR0_PTXnI ( 0XF << 4)

#define IMR0_PRXI ( 1 << 0)
#define IMR0_RCABT (1 << 1)
#define IMR0_RACEI (1 << 2)
#define IMR0_FLONI (1 << 3)
#define IMR0_OVFI (1 << 4)
#define IMR0_LSTE0I ( 1 << 5)
#define IMR0_LSTPE0I ( 1 << 6)
#define IMR0_SRCI (1 << 7)

#define IMR0_TMR0I ( 1 << 0)
#define IMR0_TMR1I ( 1 << 1)
#define IMR0_PWEI (1 << 2)
#define IMR0_PHYI (1 << 3)
#define IMR0_SHDNII (1 << 4)
#define IMR0_MIBFI (1 << 5)
#define IMR0_UDPI ( 1 << 6)

#define IMR0_RXSTL0I (1 << 0)
#define IMR0_TXSTLI (1 << 1)

/*Interrupt Enable Clear Register（mask) (IMR0C,IMR1C,IMR2C,IMR3C)*/

#define IMR0C_PPRX0I (1 << 0)
#define IMR0C_PPTXI ( 1 << 1)
#define IMR0C_PXR0I (1 << 2)
#define IMR0C_PTXI (1 << 3)
#define IMR0C_PTXnI ( 0XF << 4)

#define IMR0C_PRXI ( 1 << 0)
#define IMR0C_RCABT (1 << 1)
#define IMR0C_RACEI (1 << 2)
#define IMR0C_FLONI (1 << 3)
#define IMR0C_OVFI (1 << 4)
#define IMR0C_LSTE0I ( 1 << 5)
#define IMR0C_LSTPE0I ( 1 << 6)
#define IMR0C_SRCI (1 << 7)

#define IMR0C_TMR0I ( 1 << 0)
#define IMR0C_TMR1I ( 1 << 1)
#define IMR0C_PWEI (1 << 2)
#define IMR0C_PHYI (1 << 3)
#define IMR0C_SHDNII (1 << 4)
#define IMR0C_MIBFI (1 << 5)
#define IMR0C_UDPI ( 1 << 6)

#define IMR0C_RXSTL0I (1 << 0)
#define IMR0C_TXSTLI (1 << 1)

/*Tx Descriptor Control Status Register*/
#define TDCSR_RUN0 (1 << 0)
#define TDCSR_ACT0 ( 1 << 1)
#define TDCSR_WAK0 (1 << 2)
#define TDCSR_DEAD0 ( 1 << 3)

#define TDCSR_RUN1 ( 1 << 4)
#define TDCSR_ACT1 (1 << 5)
#define TDCSR_WAK1 ( 1 << 6)
#define TDCSR_DEAD1 ( 1 << 7)

#define TDCSR_RUN2 ( 1 << 0)
#define TDCSR_ACT2 ( 1 << 1)
#define TDCSR_WAK2 ( 1 << 2)
#define TDCSR_DEAD2 ( 1 << 3)

#define TDCSR_RUN3 ( 1 << 4)
#define TDCSR_ACT3 ( 1 << 5)
#define TDCSR_WAK3 ( 1 << 6)
#define TDCSR_DEAD3 ( 1 << 7)

/*Tx Descriptor Control Status Clear Register*/
#define TDCSRC_RUN0 (1 << 0)
#define TDCSRC_ACT0 ( 1 << 1)
#define TDCSRC_WAK0 (1 << 2)
#define TDCSRC_DEAD0 ( 1 << 3)

#define TDCSRC_RUN1 ( 1 << 4)
#define TDCSRC_ACT1 (1 << 5)
#define TDCSRC_WAK1 ( 1 << 6)
#define TDCSRC_DEAD1 ( 1 << 7)

#define TDCSRC_RUN2 ( 1 << 0)
#define TDCSRC_ACT2 ( 1 << 1)
#define TDCSRC_WAK2 ( 1 << 2)
#define TDCSRC_DEAD2 ( 1 << 3)

#define TDCSRC_RUN3 ( 1 << 4)
#define TDCSRC_ACT3 ( 1 << 5)
#define TDCSRC_WAK3 ( 1 << 6)
#define TDCSRC_DEAD3 ( 1 << 7)

/*Pending Timer for Tx Queue/Rx Queue Empty Interrupt*/
#define	TQETMR_OFFSET  (0x3f<<0)
#define TQETMS_OFFSET  (0x3 << 6)

#define RQETMR_OFFSET (0x3f << 0)
#define RQETMS_OFFSET (0x3 << 6)







#define ZXIW_STATUS_LINK 0x02
#define ZXIW_CTRL_TFCE	 0x40
#define ZXIW_CTRL_RFCE	 0x20
#define ZXIW_CTRL_XONEN	 0x80
#define MIBCR_MIBCLR        0x01


/* PHY 1000 MII Register/Bit Definitions */
/* PHY Registers defined by IEEE */
#define PHY_CTRL         0x00 /* Control Register */
#define PHY_STATUS       0x01 /* Status Regiser */
#define PHY_ID1          0x02 /* Phy Id Reg (word 1) */
#define PHY_ID2          0x03 /* Phy Id Reg (word 2) */
#define PHY_AUTONEG_ADV  0x04 /* Autoneg Advertisement */
#define PHY_LP_ABILITY   0x05 /* Link Partner Ability (Base Page) */
#define PHY_AUTONEG_EXP  0x06 /* Autoneg Expansion Reg */
#define PHY_NEXT_PAGE_TX 0x07 /* Next Page TX */
#define PHY_LP_NEXT_PAGE 0x08 /* Link Partner Next Page */
#define PHY_1000T_CTRL   0x09 /* 1000Base-T Control Reg */
#define PHY_1000T_STATUS 0x0A /* 1000Base-T Status Reg */
#define PHY_EXT_STATUS   0x0F /* Extended Status Reg */




/* PHY Control Register */
#define MII_CR_SPEED_SELECT_MSB 0x0040 /* bits 6,13: 10=1000, 01=100, 00=10 */
#define MII_CR_COLL_TEST_ENABLE 0x0080 /* Collision test enable */
#define MII_CR_FULL_DUPLEX      0x0100 /* FDX =1, half duplex =0 */
#define MII_CR_RESTART_AUTO_NEG 0x0200 /* Restart auto negotiation */
#define MII_CR_ISOLATE          0x0400 /* Isolate PHY from MII */
#define MII_CR_POWER_DOWN       0x0800 /* Power down */
#define MII_CR_AUTO_NEG_EN      0x1000 /* Auto Neg Enable */
#define MII_CR_SPEED_SELECT_LSB 0x2000 /* bits 6,13: 10=1000, 01=100, 00=10 */
#define MII_CR_LOOPBACK         0x4000 /* 0 = normal, 1 = loopback */
#define MII_CR_RESET            0x8000 /* 0 = normal, 1 = PHY reset */

/* PHY Status Register */
#define MII_SR_EXTENDED_CAPS     0x0001	/* Extended register capabilities */
#define MII_SR_JABBER_DETECT     0x0002	/* Jabber Detected */
#define MII_SR_LINK_STATUS       0x0004	/* Link Status 1 = link */
#define MII_SR_AUTONEG_CAPS      0x0008	/* Auto Neg Capable */
#define MII_SR_REMOTE_FAULT      0x0010	/* Remote Fault Detect */
#define MII_SR_AUTONEG_COMPLETE  0x0020	/* Auto Neg Complete */
#define	MII_SR_UD_ABILITY		 0x0080
#define MII_SR_PREAMBLE_SUPPRESS 0x0040	/* Preamble may be suppressed */
#define MII_SR_EXTENDED_STATUS   0x0100	/* Ext. status info in Reg 0x0F */
#define MII_SR_100T2_HD_CAPS     0x0200	/* 100T2 Half Duplex Capable */
#define MII_SR_100T2_FD_CAPS     0x0400	/* 100T2 Full Duplex Capable */
#define MII_SR_10T_HD_CAPS       0x0800	/* 10T   Half Duplex Capable */
#define MII_SR_10T_FD_CAPS       0x1000	/* 10T   Full Duplex Capable */
#define MII_SR_100X_HD_CAPS      0x2000	/* 100X  Half Duplex Capable */
#define MII_SR_100X_FD_CAPS      0x4000	/* 100X  Full Duplex Capable */
#define MII_SR_100T4_CAPS        0x8000	/* 100T4 Capable */

/* PHY Link Partner Ability Register */
#define MII_LPAR_LPACK           0x4000 /* Acked by link partner */



enum ZXIW_registers {

	MAC = 0,
	NODE_CTRL = 0x04,
	RCR	= 0x06,
	TCR	= 0x07,
	CR0_SET	= 0x08,
	CR1_SET	= 0x09,
	CR2_SET	= 0x0a,
	CR3_SET = 0x0b,
	CR0_CLR	= 0x0c,
	CR1_CLR = 0x0d,
	CR2_CLR = 0x0e,
	CR3_CLR = 0x0f,
	MAR = 0x10,
	MAR_4_7	= 0x14,
	DEC_BASE_HI	= 0x18,
	DBF_BASE_HI	= 0x1c,
	ISR_CTL		= 0x20,
	ISR_HOTMR	= 0x20,
	ISR_CTL1	= 0x21,
	TXE_SR		= 0x22,
	RX0E_SR		= 0x23,
	ISR		= 0x24,
	ISR0		= 0x24,
	ISR1		= 0x25,
	ISR2		= 0x26,
	ISR3		= 0x27,
	IMR		= 0x28,
	IMR0		= 0x28,
	IMR1		= 0x29,
	IMR2		= 0x2a,
	IMR3		= 0X2b,
	IMRC		= 0x2c,
	IMRC0		= 0x2c,
	IMRC1		= 0x2d,
	IMRC2		= 0x2e,
	IMRC3		= 0x2f,
	TDCSR_SET	= 0x30,
	TDCSR_CLR	= 0x34,
	QEMPTYR		= 0x3c,

	TQETMR		= 0x3e,
	RQETMR		= 0x3f,

	TDBASE_LO	= 0x40,
	OTDSIZE		= 0x50,
	TDCSIZE		= 0x52,
	TDINDX		= 0x54,
	TDINDX0		= 0x54,
	TDINDX1		= 0x56,
	TDINDX2		= 0x58,
	TDINDX3		= 0x5a,
	PAUSE_TIMER	= 0x5c,
	
	FIFO_TEST1	= 0x64,
	REG_68h		= 0x68,
	CAMCR		= 0x69,
	GFTEST		= 0x6a,
	FTSTCMD		= 0x6b,
	MIICFG		= 0x6c,
	MIISR		= 0x6d,
	PHYSR0		= 0x6e,
	PHYSR1		= 0x6f,
	MIICR		= 0x70,
	MIIADR		= 0x71,
	MIIDATA		= 0x72,
	SOFT_TIMER0	= 0x74,
	SOFT_TIMER1	= 0x76,
	CFGA		= 0x78,
	CFGB		= 0x79,
	CFGC		= 0x7a,
	CFGD		= 0x7b,
	
	DCFG0		= 0x7c,
	DCFG1		= 0x7d,
	MCFG0		= 0x7e,
	MCFG1		= 0x7f,


	TBIST		= 0x80,
	RBIST		= 0x81,
	PMCC		= 0x82,
	STICKHW		= 0x83,
	MIBCR		= 0x84,
	EERSV		= 0x85,	
	REVID		= 0x86,
	MIBREAD		= 0x88,
	MIBDATA		= 0x88,
	BPMA		= 0x8c,
	EEWR_DATA	= 0x8c,
	BPMD_WR		= 0x8f,
	BPCMD		= 0x90,
	BPMD_RD		= 0x91,
	EECHKSUM	= 0x92,
	EECSR		= 0x93,
	EERD_DATA	= 0x94,
	EADDR		 = 0x96,
	EMBCMD		= 0x97,
	JMPSR0		= 0x98,
	JMPSR1		= 0x99,
	JMPSR2		= 0x9a,
	JMPSR3		= 0x9b,
	CHIPGSR		= 0x9c,
	TESTCFG		= 0x9d,
	DEBUG		= 0x9e,
	CHIPGCR		= 0x9f,
	
	WOLCR0_SET	= 0xa0,
	WOLCR1_SET	= 0xa1,
	PWCFG_SET	= 0xa2,
	WOLCFG_SET	= 0xa3,
	WOLCR0_CLR	= 0xa4,
	WOLCR1_CLR	= 0xa5,
	PWCFG_CLR	= 0xa6,
	WOLCFG_CLR	= 0xa7,
	WOLSR0_SET	= 0xa8,
	WOLSR1_SET	= 0xa9,
	WOLSR0_CLR	= 0xac,
	WOLSR1_CLR	= 0xad,
	PATRN_CRC0	= 0xb0,
	PATRN_CRC1	= 0xb2,
	PATRN_CRC2	= 0xb4,
	PATRN_CRC3	= 0xb6,
	PATRN_CRC4	= 0xb8,
	PATRN_CRC5	= 0xba,
	PATRN_CRC6	= 0xbc,
	PATRN_CRC7	= 0xbe,

	MIBEXTREME	= 0x108,
	MIBHIGH		= 0x10c,
	MIBLOW		= 0x110,
	MIBMINIMAL	= 0x114,
	TSUPPTHR0	= 0x118,
	TSUMED		= 0x119,
	TSUHIG		= 0x11a,
	TSUEXT		= 0x11b,
	TSUPPTHR1	= 0x11c,
	RSUPPTHR0	= 0x120,
	RSUMED		= 0x121,
	RSUHIG		= 0x122,
	RSUEXT		= 0x123,
	
	RSUPPTHR1	= 0x124,
	IMTIMER		= 0x128,
	
	RSSCMD		 = 0x12c,
	INDTABLE0	= 0X130,
	RSSKEY0		= 0X1B0,
	
	RD0INDX		= 0x1d8,
	RD2INDX		= 0x1dc,
	RD4INDX		= 0x1e0,
	RD6INDX		= 0x1E4,
	
	NEWFEATURE	= 0x1e8,
	RD0CSR_SET	= 0x1ec,
	RD2CSR_SET	= 0x1ed,
	RD4CSR_SET	= 0x1EE,
	RDCCSR_SET	= 0x1ef,
	RD0CSR_CLR	= 0x1f0,
	RD2CSR_CLR	= 0x1f1,
	RD4CSR_CLR	= 0x1f2,
	RD6CSR_CLR	= 0x1f3,

	RD0BASE_LO	= 0x1f4,
	RD1BASE_LO	= 0x1f8,
	RD2BASE_LO	= 0x1fc,
	RD3BASE_LO	= 0x200,
	RD4BASE_LO	= 0x204,
	RD5BASE_LO	= 0x208,
	RD6BASE_LO	= 0X20C,
	RD7BASE_LO	= 0x210,
	
	RD0CSIZE	= 0x214,
	RD2CSIZE	= 0x218,
	RD4CSIZE	= 0x21c,
	RD6CSIZE	= 0x220,

	R0BRDU		= 0x224,
	R2BRDU		= 0x228,
	R4BRDU		= 0x22c,
	R6BRDU		= 0x230,
	
	RSUPPTHR	= 0x236,
	TSUPPTHR	= 0x237,
	ACAM0		= 0x238,
	VCAM0		= 0x438,
	ACAMM1		= 0x538,
	VCAMM1		= 0x540,
	
	BYTEMSK0_0	= 0x550,
	BYTEMSK0_1	= 0x554,
	BYTEMSK0_2	= 0x558,
	BYTEMSK0_3	= 0x55c,
	
	BYTEMSK1_0	= 0x560,
	BYTEMSK1_1	= 0x564,
	BYTEMSK1_2	= 0x568,
	BYTEMSK1_3	= 0x56c,
	
	BYTEMSK2_0	= 0x570,
	BYTEMSK2_1	= 0X574,
	BYTEMSK2_2	= 0X578,
	BYTEMSK2_3	= 0x57c,

	BYTEMSK3_0	= 0x580,
	BYTEMSK3_1	= 0x584,
	BYTEMSK3_2	= 0x588,
	BYTEMSK3_3	= 0x58c,

	BYTEMSK4_0	= 0x590,
	BYTEMSK4_1	= 0x594,
	BYTEMSK4_4	= 0x598,
	BYTEMSK4_3	= 0x59c,

	BYTEMSK5_0	= 0x5a0,
	BYTEMSK5_1	= 0x5a4,
	BYTEMSK5_2	= 0x5a8,
	BYTEMSK5_3	= 0x5ac,
		
			
	BYTEMSK6_0	= 0x5b0,
	BYTEMSK6_1	= 0x5b4,
	BYTEMSK6_2	= 0x5b8,
	BYTEMSK6_3	= 0x5bc,

	BYTEMSK7_0	= 0x5c0,
	BYTEMSK7_1	= 0x5c4,
	BYTEMSK7_2	= 0x5c8,
	BYTEMSK7_3	= 0x5cc,

	MDIOPA		= 0x5d0,
	DBGSEL		= 0x5d4,
	VLSA_ARP_NS	= 0x5d9,
	ARPNSEN		= 0x600,
	ARPLCIPA	= 0x604,
	ARPRMIPA	= 0x608,

	DYNAMIC_CLOCK	= 0x5dc,
	DELAY_COMP0	= 0x5e0,
	DELAY_COMP1	= 0x5e4,
	DELAY_COMP2	= 0x5e8,
	NSLCIPA3	= 0x5ec,

	REMOTE_IPV6_0	= 0x610,
	REMOTE_IPV6_1	= 0x614,
	REMOTE_IPV6_2	= 0x618,
	REMOTE_IPV6_3	= 0x61c,

	SOLI0_0		= 0x620,
	SOLI0_1		= 0x624,
	SOLI0_2		= 0x628,
	SOLI0_3		= 0x62c,

	SOLI1_0		= 0x630,
	SOLI1_1		= 0x634,
	SOLI1_2		= 0x638,
	SOLI1_3		= 0x63c,

	TARGET0_IPV60_0	= 0x640,
	TARGET0_IPV60_1	= 0x644,
	TARGET0_IPV60_2	= 0x648,
	TARGET0_IPV60_3	= 0x64c,

	
	TARGET0_IPV61_0	= 0x650,
	TARGET0_IPV61_1	= 0x654,
	TARGET0_IPV61_2	= 0x658,
	TARGET0_IPV61_3	= 0x65b,//maybe some problem.
	
	TARGET1_IPV60_0	= 0x660,
	TARGET1_IPV60_1	= 0x664,
	TARGET1_IPV60_2	= 0x668,
	TARGET1_IPV60_3	= 0x66c,
	
	TARGET1_IPV61_0	= 0x670,
	TARGET1_IPV61_1	= 0x674,
	TARGET1_IPV61_2	= 0x678,
	TARGET1_IPV61_3	= 0x67c,
	
	SRSSKEY0	= 0x700,
	SRSSCMD		= 0x728,
	
	RXWRDATA0	= 0x7a0,
	RXWRDATA1	= 0x7a4,
	
	RXSTATUS	= 0x7a8,
	RXBNRYCURR	= 0x7ac,
	TXRDDATA0	= 0x7b0,
	TXRDDATA1	= 0x7b4,
	TXSTATUS	= 0x7b8,
	TXBNRCURR	= 0x7bc,
	MEMBIST		= 0x7c0,
	SRAMBIT1	= 0x7c4,
	SRAMBIT2	= 0x7c8,

	ISR4		= 0x750,
	ISR5		= 0x751,
	ISR6		= 0x752,
	
	NEWISR456	= 0x753,
	ISR7		= 0x754,
	ISR8		= 0x755,
	ISR9		= 0X756,
	NEWISR789	= 0x757,
	ISR10		= 0x758,
	NEWISR10	= 0x75b,
	
	IMR456		= 0x75c,
	IMR789		= 0x760,
	IMR10		= 0x764,

	IMRC456		= 0x768,
	IMCR789		= 0x76c,
	IMCR10		= 0x770,
	
	RX1E_SR		= 0x774,
	RX3E_SR		= 0x775,
	RX7E_SR		= 0x777,
};

#endif
