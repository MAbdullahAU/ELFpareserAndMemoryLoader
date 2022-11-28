# ELFpareserAndMemoryLoader
This belongs to Advance Operating System Assignment One ( NUST - SEECS )

1.  Code getter From Win.txt is an example for mmap(), this fuction map the object file to mamory
2a. CompileAndRun.sh takes ParseElf.c and complie to give ParseElf.o 
2b. CompileAndRun.sh takes ParseElf.o and MyElf.h and make an executable called GoElf
3.  PareElf.c consumes the following file
    FILE* fin = fopen("Tester", "rb");
    FILE* fout = fopen("TesterResults.txt","wb");  // w for write, b for binary
    FILE* ftest = fopen("Random.txt","wb");
4.  Test.c is a simple helloWorld code which is Compled and assembled to Tester
5. This Tester Executable is used to map on the memory
