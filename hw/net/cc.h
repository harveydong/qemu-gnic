#ifndef __CC_H__
#define __CC_H_


typedef unsigned char u8_t;
typedef signed char s8_t;

typedef unsigned short u16_t;
typedef signed short s16_t;

typedef unsigned int u32_t;
typedef signed int s32_t;

typedef unsigned int sys_prot_t; //
typedef unsigned int mem_ptr_t;


#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_STRUCT
#define PACK_STRUCT_BEGIN __packed
#define PACK_STRUCT_END

#define LWIP_DEBUG
#define LWIP_PLATFORM_DIAG(x) {printf(x);}
#define LWIP_PLATFORM_ASSERT(x) {printf(x);while(1);}

#define LWIP_ERROR(message,expression,handler) \
	do {if(!(expression)){\
			printf(message);handler;}}while(0)	
		
#define U16_F "u"
#define S16_F "d"
#define X16_F "x"
#define U32_F "u"
#define S32_F "d"
#define X32_F "x"

#define LWIP_PROVIDE_ERRNO
#define BYTE_ORDER_LITTLE_ENDIAN

extern unsigned int sys_now(void);



#endif
