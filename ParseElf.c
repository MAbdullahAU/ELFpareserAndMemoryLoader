#include <stdio.h>
#include <stdlib.h>
#include "MyElf.h"
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

struct elf64_hdr header;


int main(int argc, char** argv, char** envp)
{
    //int (*ptr)(int, char **, char**);

    FILE* fin = fopen("Tester", "rb");
    FILE* fout = fopen("TesterResults.txt","wb");  // w for write, b for binary
    FILE* ftest = fopen("Random.txt","wb");

   // fwrite(buffer,sizeof(buffer),1,fout); // write 10 bytes from our buffer
    //if(fin) 
    //{

        fread(&header, sizeof(header), 1, fin); // // read the header Note: size_t fread(void *ptr, size_t size, size_t nmemb, fin *stream);
        
        printf("the elf magic is \n%02X\t%02X\t%02X\t%02X\n", header.e_ident[EI_MAG0], header.e_ident[EI_MAG1],header.e_ident[EI_MAG2],header.e_ident[EI_MAG3]); // check so its really an elf fin
        
        if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0)  //line 344
        {
            printf("ELF\n ");     
        }
        //printf("the elf class is %d", header.e_ident[EI_CLASS]); 
        
        if (header.e_ident[EI_CLASS] == ELFCLASS64)
        {
            printf("\nThe classs is ELF64 \n");
        }

        if(header.e_type == 0x01)
        {
            printf("\nIt is a Relocatable fin");
        }
        else if(header.e_type == 0x02)
        {
            printf("\nIt is a Executable fin");
        }
        else
        {
            printf("\nIt is something else");
        }
        
        printf("\n");

        // Now printring The
        //header.e_phoff; //Start of the program header Table
        //header.e_phentsize; //Size of program header table entries
        //header.e_phnum; //no of entries in program header table
        //header.e_ehsize; //elf header size

        

    //}

    fclose(fin);  // finally close the fin



    //--------------------------------------Parcing the Progarm header table

    fin = fopen("Tester", "rb");
    

    //if(fin)
    //{
        struct elf64_phdr PHT[header.e_phnum];

        int i;
        fseek( fin, 64, SEEK_SET );
        for(i = 0; i < header.e_phnum; i++)
            fread(&PHT[i], header.e_phentsize, 1, fin);
        

        char* bufferPtr =  malloc (5);
        int fileSize = 24000;

        for(i = 0; i < header.e_phnum; i++)
        {
            printf("\nFirst Few Bits of PH %d \n type ->  %02X\t Flags -> %02X\t offset -> %llX\t p_vaddr -> %llX\t paddr -> %llX\t filesz -> %llX\t memsz -> %llX\t flags -> %X\t align -> %llX\n", i, PHT[i].p_type, PHT[i].p_flags ,PHT[i].p_offset, PHT[i].p_vaddr, PHT[i].p_paddr, PHT[i].p_filesz, PHT[i].p_memsz, PHT[i].p_flags, PHT[i].p_align);
            
            if(PHT[i].p_type == 0x01)
            {
                bufferPtr =   realloc(bufferPtr, PHT[i].p_filesz);
                
                fwrite(&PHT[i].p_filesz,sizeof(PHT[i].p_filesz),1,ftest);
                //fileSize = fileSize + (int)PHT[i].p_memsz;


                fseek( fin, PHT[i].p_offset , SEEK_SET );
                fread(bufferPtr, PHT[i].p_memsz, 1, fin);
                
                fwrite(bufferPtr, PHT[i].p_memsz, 1, fout);
                
                
                /*
                //fwrite(&PHT[i].p_type,4,1,fout);
                fwrite(&PHT[i].p_type,sizeof(PHT[i].p_type),1,fout);
                //fwrite(&PHT[i].p_flags,4,1,fout);
                fwrite(&PHT[i].p_flags,sizeof(PHT[i].p_flags),1,fout);
                //fwrite(&PHT[i].p_offset,8,1,fout);
                fwrite(&PHT[i].p_offset,sizeof(PHT[i].p_offset),1,fout);
                //fwrite(&PHT[i].p_vaddr,8,1,fout);
                fwrite(&PHT[i].p_vaddr,sizeof(PHT[i].p_vaddr),1,fout);
                //fwrite(&PHT[i].p_paddr,8,1,fout);
                fwrite(&PHT[i].p_paddr,sizeof(PHT[i].p_paddr),1,fout);
                //fwrite(&PHT[i].p_filesz,8,1,fout);
                fwrite(&PHT[i].p_filesz,sizeof(PHT[i].p_filesz),1,fout);
                //fwrite(&PHT[i].p_memsz,8,1,fout);
                fwrite(&PHT[i].p_memsz,sizeof(PHT[i].p_memsz),1,fout);
                //fwrite(&PHT[i].p_align,8,1,fout);
                fwrite(&PHT[i].p_align,sizeof(PHT[i].p_align),1,fout);
                */
            
                fwrite("\n",1,1,fout);
            }
        }

        fclose(fin);
        fclose(fout);
        
        //fout = open("TesterResults.txt", O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
        fout = fopen("TesterResults.txt","rb");
        
                return(0);

        bufferPtr =   realloc(bufferPtr, fileSize);
        fread(bufferPtr, fileSize,1, fout);

        char* map = mmap(0, fileSize, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED, -1, 0);
        
        if (map == MAP_FAILED) 
            perror("Error mmapping the fin");
        
        ////-------------------------MApping of fin
        for (i = 1; i <= fileSize; ++i) 
        {
            //map[i] = 2 * i;
            map[i] = bufferPtr[i]; 
        }


        ////-------------------------Releasing Mapped Memory
        if (munmap(map, fileSize) == -1) 
            perror("Error un-mmapping the fin");

        free(bufferPtr);
        fclose(fout);
        return 0;
        

    
    //}



//return ptr(argc,argv,envp);
}
