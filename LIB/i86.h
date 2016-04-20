#ifndef _REGS_H
#define _REGS_H

/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
extern int _8087;

int _detect_80387(void);

struct DWORDREGS {
	unsigned long edi;
	unsigned long esi;
	unsigned long ebp;
	unsigned long cflag;
	unsigned long ebx;
	unsigned long edx;
	unsigned long ecx;
	unsigned long eax;
	unsigned short eflags;
};

struct DWORDREGS_W {
	unsigned long di;
	unsigned long si;
	unsigned long bp;
	unsigned long cflag;
	unsigned long bx;
	unsigned long dx;
	unsigned long cx;
	unsigned long ax;
	unsigned short flags;
};

struct WORDREGS {
	unsigned short di, _upper_di;
	unsigned short si, _upper_si;
	unsigned short bp, _upper_bp;
	unsigned short cflag, _upper_cflag;
	unsigned short bx, _upper_bx;
	unsigned short dx, _upper_dx;
	unsigned short cx, _upper_cx;
	unsigned short ax, _upper_ax;
	unsigned short flags;
};

struct BYTEREGS {
	unsigned short di, _upper_di;
	unsigned short si, _upper_si;
	unsigned short bp, _upper_bp;
	unsigned long cflag;
	unsigned char bl;
	unsigned char bh;
	unsigned short _upper_bx;
	unsigned char dl;
	unsigned char dh;
	unsigned short _upper_dx;
	unsigned char cl;
	unsigned char ch;
	unsigned short _upper_cx;
	unsigned char al;
	unsigned char ah;
	unsigned short _upper_ax;
	unsigned short flags;
};

union REGS {		/* Compatible with DPMI structure, except cflag */
	struct DWORDREGS d;
#ifdef _NAIVE_DOS_REGS
	struct WORDREGS x;
#else
#ifdef _BORLAND_DOS_REGS
	struct DWORDREGS x;
#else
	struct DWORDREGS x;
#endif
#endif
	struct WORDREGS w;
	struct BYTEREGS h;
};

struct SREGS {
	unsigned short es;
	unsigned short ds;
	unsigned short fs;
	unsigned short gs;
	unsigned short cs;
	unsigned short ss;
};

struct ftime {
	unsigned ft_tsec : 5;	/* 0-29, double to get real seconds */
	unsigned ft_min : 6;	/* 0-59 */
	unsigned ft_hour : 5;	/* 0-23 */
	unsigned ft_day : 5;	/* 1-31 */
	unsigned ft_month : 4;	/* 1-12 */
	unsigned ft_year : 7;	/* since 1980 */
};

struct date {
	short da_year;
	char  da_day;
	char  da_mon;
};

struct time {
	unsigned char ti_min;
	unsigned char ti_hour;
	unsigned char ti_hund;
	unsigned char ti_sec;
};

struct dfree {
	unsigned df_avail;
	unsigned df_total;
	unsigned df_bsec;
	unsigned df_sclus;
};
#endif
