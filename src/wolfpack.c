#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include <wolfpack.h>

int count;
unsigned long source_address;
unsigned long destination_address;
unsigned long source_port;
unsigned long destination_port;
unsigned long fragment_offset;
unsigned long flag;
unsigned long total_length; 
unsigned long checksum;
unsigned long payload;

unsigned long calculated_checksum;
int payload_length; 

void compute(const unsigned char *tobecomputed)
{
 source_address=0;
 destination_address=0;
 source_port=0;
 destination_port=0;
 fragment_offset=0;
 flag=0;
 total_length=0;
 checksum=0;
 payload=0;
 count=0;
 payload_length=0;

 for(int i=0;i<5;i++)
 {
   source_address=source_address|tobecomputed[count];
   count++;
   if(i!=4)
   source_address=source_address<<8;
 }

 for(int i=0;i<5;i++)
 {
   destination_address=destination_address|tobecomputed[count];
   count++;
   if(i!=4)
   destination_address=destination_address<<8;
 }
    source_port=source_port|tobecomputed[count];
    count++;


    destination_port=destination_port|tobecomputed[count];
    count++;

 for(int i=0;i<3;i++)
 {
  fragment_offset=fragment_offset|tobecomputed[count];
  count++;

  if(i!=2)
  fragment_offset=fragment_offset<<8;
 }

for(int i=0;i<2;i++)
 {
  flag=flag|tobecomputed[count];
  count++;
  if(i!=1)
  flag=flag<<8;
 }
 for(int i=0;i<3;i++)
 {
  total_length=total_length|tobecomputed[count];
  count++;
  if(i!=2)
  total_length=total_length<<8;
 }

for(int i=0;i<4;i++)
 {
  checksum=checksum|tobecomputed[count];
  count++;
  if(i!=3)
  checksum=checksum<<8;
 }

 payload_length=total_length-24;
}

char c;
void print_packet_sf(const unsigned char *packet) {

  compute(packet);

printf("%010lx\n",source_address); 
printf("%010lx\n",destination_address);
printf("%02lx\n",source_port);
printf("%02lx\n",destination_port);
printf("%06lx\n",fragment_offset);
printf("%04lx\n",flag);
printf("%06lx\n",total_length);
printf("%08lx\n",checksum);

for(int i=0;i<payload_length;i++)
{
  c= packet[count];
  printf("%c",c);
  count++;
  if(i==payload_length-1)
  printf("\n");
}
}

unsigned int checksum_sf(const unsigned char *packet) {

    calculated_checksum=0;
    compute(packet);

    calculated_checksum=calculated_checksum+source_address;
    calculated_checksum=calculated_checksum+destination_address;
    calculated_checksum=calculated_checksum+source_port;
    calculated_checksum=calculated_checksum+destination_port;
    calculated_checksum=calculated_checksum+fragment_offset;
    calculated_checksum=calculated_checksum+flag;
    calculated_checksum=calculated_checksum+total_length;
    calculated_checksum=calculated_checksum% ((long)(pow(2,32)-1));

return (unsigned int) calculated_checksum;
}


int bytes_needed;
int returning_packets;
int count_of_message_characters_used;
char store;
int message_length;
int current_message_index;
int remaining_index;

unsigned int totalLength;
unsigned int offsetflag;
unsigned int check_sum;

unsigned long src_addr_temp;
unsigned long dest_addr_temp;
unsigned short flags_temp;

//const unsigned char* packet_array[21];

unsigned int packetize_sf(const char *message, unsigned char *packets[], unsigned int packets_len, unsigned int max_payload,
    unsigned long src_addr, unsigned long dest_addr, unsigned short flags) {

    bytes_needed=0;
    returning_packets=0;
    remaining_index=0;
    count_of_message_characters_used=0;
    message_length=strlen(message);
    bytes_needed=24+max_payload;
  
    for(int i=0;i<packets_len;i++)
    {
      src_addr_temp=src_addr;
      dest_addr_temp=dest_addr;
      flags_temp=flags;
      check_sum=0;

      if(message_length>current_message_index)
    { 
      returning_packets=returning_packets+1;
      packets[i]=malloc(bytes_needed);

      offsetflag=current_message_index;
      remaining_index=message_length-current_message_index;
      if(remaining_index>max_payload){
      remaining_index=max_payload;
      current_message_index=current_message_index+max_payload;
      totalLength=max_payload+24;
      }

      else{
      current_message_index=current_message_index+remaining_index;
       totalLength=remaining_index+24;
      }
      
     for(int j=4;j>=0;j--)
     {
      //printf("%010lx\n",src_addr); 
      store=src_addr_temp&0x00000000FF;  
      src_addr_temp=src_addr_temp>>8;

       //printf("%010lx\n",src_addr); 
      //printf("%02x\n",store);  
                                
      packets[i][j]=store;
     }
     
     for(int j=9;j>=5;j--)
     {
      store=dest_addr_temp&0x00000000FF;
      dest_addr_temp=dest_addr_temp>>8;

      packets[i][j]=store;
     }

     packets[i][10]=0x20;
     packets[i][11]=0x40;

     for(int j=14;j>=12;j--)
     {
      store=offsetflag& 0x000000FF;
      offsetflag=offsetflag>>8;
      packets[i][j]=store;
     }
     
     for(int j=16;j>=15;j--)
     {
       store=flags_temp&0x00FF;
       flags_temp=flags_temp>>8;

       packets[i][j]=store;
     }

      for(int j=19;j>=17;j--)
     {
      store=totalLength& 0x000000FF;
      totalLength=totalLength>>8;
      packets[i][j]=store;
     }

     //strncpy(packet_array,packets[i],20);
     //packet_array[20]='\0';
     //check_sum=checksum_sf(packet_array);

      check_sum=checksum_sf(packets[i]);

      for(int j=23;j>=20;j--)
     {
      store=check_sum& 0x000000FF;
      check_sum=check_sum>>8;
      packets[i][j]=store;
     }

     for(int j=24;j<24+remaining_index;j++)
     {
       packets[i][j]=message[count_of_message_characters_used];
       count_of_message_characters_used=count_of_message_characters_used+1;
     }

     //print_packet_sf(packets[i]);

    }

    }
    return returning_packets;
}

int current_message_len;
int currentCheckSum;
int currentStart;
int toBeReturned;
int number_of_times_it_will_run;
bool isWritten=false;
unsigned int reconstruct_sf(unsigned char *packets[], unsigned int packets_len, char *message, unsigned int message_len) {
  current_message_len=0;
  currentCheckSum=0;
  currentStart=0;
  toBeReturned=0;
  number_of_times_it_will_run=0;

  for(int i=0;i<packets_len;i++)
  {
    unsigned char* packet = packets[i] ;
    currentCheckSum=checksum_sf(packet);

    if(currentCheckSum==checksum)
    {
     currentStart=fragment_offset;
     //printf("yep\n");
    //printf("%d\n",currentStart);

     if(currentStart<=message_len-1)
     {
      isWritten=true;
      toBeReturned=toBeReturned+1;
     
      number_of_times_it_will_run=message_len-1-currentStart;

      if(number_of_times_it_will_run>payload_length)
      number_of_times_it_will_run=payload_length;

      for(int j=0;j<number_of_times_it_will_run;j++)
      {
        message[currentStart+j]=packet[count];
       //printf("%c\n",message[currentStart+i]);
        count++;
      }

      if(current_message_len<currentStart)
     current_message_len=currentStart+number_of_times_it_will_run;
     //printf("%d\n",current_message_len);
     }
    }
    //else
   //printf("nope\n");
  }

  if(isWritten)
  message[current_message_len]=0x00;

  return toBeReturned;
}

