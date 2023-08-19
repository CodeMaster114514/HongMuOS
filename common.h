#ifndef COMMON_H
#define COMMON_H

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

typedef enum
{
	FreeMemory,
	OsData,
	OsCode,
	MMIO,
	Convention,
	ACPI,
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

typedef struct
{
	int type;
	void *PhysicalStart;
	void *VirtualStart;
	unsigned long long NumberOfPages;
} OsMemoryDescript;

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
	Video vdieo;
	MemoryMap map;
} Table;

void undraw_cursor();
void inc_cursor();
Pointer get_cursor_at();
Pointer get_cursor_end_at();
void draw_cursor();
void init_vdieo(Video *video);
void draw_at(Pointer *in, RGB *color);
void draw_rectangle(Rectangle *out);
void invert_color(RGB *color);
void draw_rectangle_invert_color(Pointer *start, Pointer *end);
void draw_font(Pointer *at, char *font);
void draw_char(char c);
void put_char(char c);
int put_string(const char *str);

void init_shell();

char *number_to_string(unsigned long long num);
char *number_to_hex_string(unsigned long long num);

void cursor_next_line();
void cursor_restart_line();

int print(const char *str, ...);

int InitMemory(MemoryMap *map);
unsigned long long GetTotalMemory();
#endif