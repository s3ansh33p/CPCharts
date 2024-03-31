ENTRY(_start);
STARTUP(crt0.o);

SECTIONS {
    start_address = 0x8CFE6000;
    . = start_address;
    .bootstrap.start : AT(start_address) {
        *(.bootstrap.start*)
    }
    
    info_address = 0x8CFE6010;
    . = info_address;
    .hollyhock_name : {
        KEEP(*(.hollyhock_name))
    }
    .hollyhock_description : {
        KEEP(*(.hollyhock_description))
    }
    .hollyhock_author : {
        KEEP(*(.hollyhock_author))
    }
    .hollyhock_version : {
        KEEP(*(.hollyhock_version))
    }

    .bootstrap : {
        *(.bootstrap.text*)
        *(.bootstrap.data*)
    }

    .text : {
        *(.text*)
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }
    
    _edata = .;
    PROVIDE(edata = .);
    
    .bss : {
        *(.bss*)
        *(COMMON)
    }
    
    _end = .;
    PROVIDE(end = .);

    .eh_frame : {
        *(.eh_frame*)
    }
}