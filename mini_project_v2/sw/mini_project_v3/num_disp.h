#ifndef NUMDISP
#define NUMDISP

const uint8_t map[0x10]={
		0b1000000,
		0b1111001,
		0b0100100,
		0b0110000,
		0b0011001,
		0b0010010,
		0b0000010,
		0b1111000,
		0b0000000,
		0b0010000,
		0b0001000,
		0b0000011,
		0b0100111,
		0b0100001,
		0b0000110,
		0b0001110
};

typedef struct pixel{
	uint8_t r,g,b;
	uint8_t empty; // needed for proper alignment
} pixel;


uint8_t byte_to_disp(uint8_t b){
	return map[b];
}

uint8_t disp_to_byte(uint8_t d){
	for (uint8_t i=0;i<16;i++){
		if (map[i]==d){return i;}
	}
	return 0;
}

void print_byte(uint8_t val, int index){
//	Index: 0, 1, 2
	uint8_t hi,lo;
	hi = byte_to_disp(val>>4);
	lo = byte_to_disp(val&0xf);
	switch(index){
	case 0:
		IOWR(NIOS_HEX_1_BASE, 0, hi);
		IOWR(NIOS_HEX_0_BASE, 0, lo);
		break;
	case 1:
		IOWR(NIOS_HEX_3_BASE, 0, hi);
		IOWR(NIOS_HEX_2_BASE, 0, lo);
		break;
	case 2:
		IOWR(NIOS_HEX_5_BASE, 0, hi);
		IOWR(NIOS_HEX_4_BASE, 0, lo);
		break;
	default:
		return;
	}
}

void print_pixel(pixel p, int debug){
	print_byte(p.r,2);
	print_byte(p.g,1);
	print_byte(p.b,0);
	if (debug)
		printf("R:%x G:%x B:%x\n", p.r, p.g, p.b);
}


#endif
