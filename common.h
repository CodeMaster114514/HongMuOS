#ifndef COMMON_H
#define COMMON_H

#ifndef Loader
typedef enum
{
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiUnacceptedMemoryType,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;
#endif

typedef enum
{
	FreeMemory,
	OsData,
	OsCode,
	UserData,
	UserCode,
	MMIO,
	ACPI,
	Reserved,
	UEFI
} OS_MEMORY_TYPE;

typedef struct
{
	unsigned int type;
	void *PhysicalStart;
	void *VirtualStart;
	unsigned long long NumberOfPages;
	unsigned long long Attribute;
	unsigned int space;
} MemoryDescript;

typedef struct OMD OsMemoryDescript;

struct OMD
{
	int type;
	void *PhysicalStart;
	void *VirtualStart;
	unsigned long long NumberOfPages;
	OsMemoryDescript *next;
};

typedef struct
{
	unsigned long long MapSize;
	MemoryDescript *MemoryMap;
	unsigned long long MapKey;
	unsigned long long DescriptSize;
	unsigned int DescriptVersion;
} MemoryMap;

typedef struct
{
	int x;
	int y;
} Pointer;

typedef struct
{
	Pointer start;
	Pointer end;
} Frame;

typedef struct
{
	char bule;
	char green;
	char red;
	char reserved;
} RGB;

typedef struct
{
	Pointer start;
	Pointer end;
	RGB *color;
} Rectangle;

typedef struct
{
	RGB *Frame;
	unsigned long long FrameBufferSize;
	unsigned int hight;
	unsigned int wight;
} Video;

typedef struct
{
	int line;
	int col;
} Cursor;

typedef struct
{
	unsigned char type;
	unsigned char len;
	unsigned char processID;
	unsigned char ACPI_ID;
	unsigned int flags;
} LACPI;

typedef struct
{
	unsigned char type;
	unsigned char len;
	unsigned char IO_ID;
	unsigned char reserved;
	unsigned int IO_ADDRESS;
} ACPI_IO;

typedef struct
{
	char signature[4];
	unsigned int len;
	unsigned char revision;
	unsigned char checksum;
	struct
	{
		unsigned short ID[6];
		unsigned long long table_ID;
		unsigned int revision;
	} OEM;
	struct
	{
		unsigned int ID;
		unsigned int revision;
	} Creator;
	unsigned int LICA; // 中断控制地址
	unsigned int flags;
} MADT;

typedef struct
{
	char signature[4];
	unsigned int len;
	unsigned char revision;
	unsigned char checksum;
	struct
	{
		unsigned short ID[6];
		unsigned long long table_ID;
		unsigned int revision;
	} OEM;
	struct
	{
		unsigned int ID;
		unsigned int revision;
	} Creator;
	void *enters_start[];
} XSDT;

typedef struct
{
	char signature[4];
	unsigned int len;
	unsigned char revision;
	unsigned char checksum;
	struct
	{
		unsigned short ID[6];
		unsigned long long table_ID;
		unsigned int revision;
	} OEM;
	struct
	{
		unsigned int ID;
		unsigned int revision;
	} Creator;
	unsigned int enters[];
} RSDT;

typedef union
{
	void *page;
	unsigned long long data;
} PTE;

typedef struct
{
	PTE pte[4096 / sizeof(union pte *)];
} PT;

typedef struct
{
	PT *pt[4096 / sizeof(PT *)];
} PD;

typedef struct
{
	PD *pd[4096 / sizeof(PD *)];
} PDPT;

typedef struct
{
	PDPT *pdpt[4096 / sizeof(PDPT *)];
} PML4;

typedef struct
{
	Video vdieo;
	MemoryMap map;
	RSDT *rsdt;
} Table;

typedef struct
{
	unsigned short limit;
	unsigned short base_low;
	unsigned char base_higt_1;
	unsigned char access;
	unsigned char FL; // Flag and Limit
	unsigned char base_high_2;
} __attribute__((packed)) GDT;


typedef struct
{
	unsigned short offset_low;
	unsigned short SS; // Segment Selector
	unsigned char reserved_1;
	unsigned char TF; // Type and Flag
	unsigned short offset_high_1;
	unsigned int offset_high_2;
	unsigned int reserved_2;
} __attribute__((packed)) IDT;

typedef struct
{
	unsigned short len;
	GDT *gdt;
} __attribute__((packed)) GDTR;

typedef struct
{
	unsigned short len;
	IDT *idt;
} __attribute__((packed)) IDTR;

// in cursor.c
void undraw_cursor();
void inc_cursor();
Pointer get_cursor_at();
Pointer get_cursor_end_at();
void draw_cursor();
void cursor_next_line();
void cursor_restart_line();

// in vdieo.c
void init_vdieo(Video *video);
void draw_at(Pointer *in, RGB *color);
void draw_rectangle(Rectangle *out);
void invert_color(RGB *color);
void draw_rectangle_invert_color(Pointer *start, Pointer *end);
void draw_font(Pointer *at, char *font);
void draw_char(char c);
void put_char(char c);
int put_string(const char *str);
void clean_all();

// in shell.c
void init_shell();

// in num.c
char *number_to_string(unsigned long long num);
char *number_to_hex_string(unsigned long long num);

// in print.c
int print(const char *str, ...);

// in memory.c
int InitMemory(MemoryMap *map);
unsigned long long GetTotalMemory();
unsigned long long GetTotalFreeMemory();
void *alloc_page(char type, OS_MEMORY_TYPE OMT);
void free_page(void *address);
void *alloc_os_data(unsigned long long len);
void free(void *p);

// in io.c
unsigned char io_in8(short port);
unsigned short io_in16(short port);
unsigned int io_in32(short port);
void io_out8(short port, unsigned char data);
void io_out16(short port, unsigned short data);
void io_out32(short port, unsigned int data);
unsigned long long get_cr3();
void get_gdtr(GDTR *gdtr);
void get_idtr(IDTR *idtr);
#endif