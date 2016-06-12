// Credit goes to Hans de Goede for d1x HMP->MID conversion code

#include <string.h>
#include "cfile.h"
#include "byteswap.h"
#include "hmp.h"

hmp_file *hmp_open(const char *filename) {
    int i;
    char buf[256];
    int32_t	data;
    CFILE *fp;
    hmp_file *hmp;
    int num_tracks;
    unsigned char *p;

    if (!(fp = cfopen((char *)filename, "rb")))
        return NULL;

    hmp = malloc(sizeof(hmp_file));
    if (!hmp) {
        cfclose(fp);
        return NULL;
    }

    memset(hmp, 0, sizeof(*hmp));

    if ((cfread(buf, 1, 8, fp) != 8) || (memcmp(buf, "HMIMIDIP", 8)))
        goto err;

    if (cfseek(fp, 0x30, SEEK_SET))
        goto err;

    if (cfread(&num_tracks, 4, 1, fp) != 1)
        goto err;

    if ((num_tracks < 1) || (num_tracks > HMP_TRACKS))
        goto err;

    hmp->num_trks = num_tracks;
    hmp->tempo = 120;

    if (cfseek(fp, 0x308, SEEK_SET))
        goto err;

    for (i = 0; i < num_tracks; i++) {
        if ((cfseek(fp, 4, SEEK_CUR)) || (cfread(&data, 4, 1, fp) != 1))
            goto err;

        data -= 12;

#if 0
        if (i == 0)  /* track 0: reserve length for tempo */
			data += sizeof(hmp_tempo);
#endif

        hmp->trks[i].len = data;

        if (!(p = hmp->trks[i].data = malloc(data)))
            goto err;

#if 0
        if (i == 0) { /* track 0: add tempo */
			memcpy(p, hmp_tempo, sizeof(hmp_tempo));
			p += sizeof(hmp_tempo);
			data -= sizeof(hmp_tempo);
		}
#endif
        /* finally, read track data */
        if ((cfseek(fp, 4, SEEK_CUR)) || (cfread(p, data, 1, fp) != 1))
            goto err;
    }
    cfclose(fp);
    return hmp;

    err:
    cfclose(fp);
    hmp_close(hmp);
    return NULL;
}

void hmp_close(hmp_file *hmp) {
	int i;

	for (i = 0; i < hmp->num_trks; i++)
		if (hmp->trks[i].data)
			free(hmp->trks[i].data);
	free(hmp);
}

static unsigned int hmptrk2mid(ubyte* data, int size, unsigned char **midbuf, unsigned int *midlen, hmp_track *trks)
{
	ubyte *dptr = data;
	ubyte lc1 = 0,last_com = 0;
	uint d;
	int n1, n2;
	unsigned int offset = *midlen;
	
	while (data < dptr + size)
	{
		if (data[0] & 0x80) {
			ubyte b = (data[0] & 0x7F);
			*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
			memcpy(&(*midbuf)[*midlen], &b, 1);
			*midlen += 1;
		}
		else {
			d = (data[0] & 0x7F);
			n1 = 0;
			while ((data[n1] & 0x80) == 0) {
				n1++;
				d += (data[n1] & 0x7F) << (n1 * 7);
			}
			n1 = 1;
			while ((data[n1] & 0x80) == 0) {
				n1++;
				if (n1 == 4)
					return 0;
			}
			for(n2 = 0; n2 <= n1; n2++) {
				ubyte b = (data[n1 - n2] & 0x7F);
				
				if (n2 != n1)
					b |= 0x80;
				*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
				memcpy(&(*midbuf)[*midlen], &b, 1);
				*midlen += 1;
			}
			data += n1;
		}
		data++;
		if (*data == 0xFF) { //meta?
			*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 3 + data[2]);
			memcpy(&(*midbuf)[*midlen], data, 3 + data[2]);
			*midlen += 3 + data[2];
			if (data[1] == 0x2F)
				break;
		}
		else {
			lc1=data[0] ;
			if ((lc1&0x80) == 0)
				return 0;
			switch (lc1 & 0xF0) {
				case 0x80:
				case 0x90:
				case 0xA0:
				case 0xB0:
				case 0xE0:
					if (lc1 != last_com)
					{
						*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
						memcpy(&(*midbuf)[*midlen], &lc1, 1);
						*midlen += 1;
					}
					*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 2);
					memcpy(&(*midbuf)[*midlen], data + 1, 2);
					*midlen += 2;
					data += 3;
					break;
				case 0xC0:
				case 0xD0:
					if (lc1 != last_com)
					{
						*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
						memcpy(&(*midbuf)[*midlen], &lc1, 1);
						*midlen += 1;
					}
					*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 1);
					memcpy(&(*midbuf)[*midlen], data + 1, 1);
					*midlen += 1;
					data += 2;
					break;
				default:
					return 0;
			}
			last_com = lc1;
		}
	}
	return (*midlen - offset);
}

ubyte tempo [19] = {'M','T','r','k',0,0,0,11,0,0xFF,0x51,0x03,0x18,0x80,0x00,0,0xFF,0x2F,0};

void hmp2mid(hmp_file *hmp, unsigned char **midbuf, unsigned int *midlen)
{
	int mi, i, j;
	short ms, time_div = 0xC0;
	
	*midlen = 0;
	time_div = hmp->tempo*1.6;
	
	// write MIDI-header
	*midbuf = (unsigned char *) malloc(4);
	memcpy(&(*midbuf)[*midlen], "MThd", 4);
	*midlen += 4;
	mi = swapint(6);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(mi));
	memcpy(&(*midbuf)[*midlen], &mi, sizeof(mi));
	*midlen += sizeof(mi);
	ms = swapshort(1);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(ms));
	memcpy(&(*midbuf)[*midlen], &ms, sizeof(ms));
	*midlen += sizeof(ms);
	ms = swapshort(hmp->num_trks);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(ms));
	memcpy(&(*midbuf)[*midlen], &ms, sizeof(ms));
	*midlen += sizeof(ms);
	ms = swapshort(time_div);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(ms));
	memcpy(&(*midbuf)[*midlen], &ms, sizeof(ms));
	*midlen += sizeof(ms);
	*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(tempo));
	memcpy(&(*midbuf)[*midlen], &tempo, sizeof(tempo));
	*midlen += sizeof(tempo);
	
	// tracks
	for (i = 1; i < hmp->num_trks; i++)
	{
		int midtrklenpos = 0;
		
		*midbuf = (unsigned char *) realloc(*midbuf, *midlen + 4);
		memcpy(&(*midbuf)[*midlen], "MTrk", 4);
		*midlen += 4;
		midtrklenpos = *midlen;
		mi = 0;
		*midbuf = (unsigned char *) realloc(*midbuf, *midlen + sizeof(mi));
		*midlen += sizeof(mi);
		mi = hmptrk2mid(hmp->trks[i].data, hmp->trks[i].len, midbuf, midlen, hmp->trks);
		mi = swapint(mi);
		memcpy(&(*midbuf)[midtrklenpos], &mi, 4);
	}
}
