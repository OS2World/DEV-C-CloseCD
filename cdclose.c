#define INCL_BASE
#define INCL_DOSMICS
#include <stdio.h>
#include <os2.h>

#define IOCTL_CDROMDISK 0x80

APIRET CDCloseTray (HFILE hCDROM,ULONG akce)
{
#define CDROMDISK_CLOSETRAY 0x45                     /* Bug in toolkit */
 UCHAR Signature[] = "CD01";
 ULONG PLength = 0;
 ULONG DLength = 0;
   struct {
      UCHAR First;
      UCHAR Last;
      ULONG Leadout;
   } DAudioDisk;

   PLength = 4;
   DLength = sizeof(DAudioDisk);
   memset(&DAudioDisk,0,DLength);

 return 
DosDevIOCtl(hCDROM,IOCTL_CDROMDISK,akce,&Signature,PLength, 
&PLength,&DAudioDisk,DLength,&DLength);


/* (CDGenericIO (hCDROM, IOCTL_CDROMDISK, CDROMDISK_CLOSETRAY)); */
} /* APIRET CDCloseTray */

void main(void)
{
 HFILE h;
 ULONG Action = 0;
 APIRET rc;
 rc=DosOpen("F:",&h,&Action,0,0,OPEN_ACTION_FAIL_IF_NEW|OPEN_ACTION_OPEN_IF_EXISTS
 ,OPEN_FLAGS_FAIL_ON_ERROR|OPEN_FLAGS_DASD|OPEN_SHARE_DENYREADWRITE|OPEN_ACCESS_READONLY,NULL);
 printf("DosOpen rc=%ld\n",rc);
 rc=CDCloseTray(h,0x44);
 printf("Eject rc=%ld\n",rc);  

 rc=CDCloseTray(h,CDROMDISK_CLOSETRAY);
 printf("CDClose rc=%ld\n",rc);  
 DosClose(h);
}
