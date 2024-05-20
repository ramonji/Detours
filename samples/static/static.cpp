//////////////////////////////////////////////////////////////////////////////
//
//  Test a detour of a member function (member.cpp of member.exe)
//
//
#include <stdio.h>

#include <windows.h>
#include <detours.h>


// 目标函数
void Target(void)
{
    printf("  Target Func! \n");
}

// Detours 必要条件1: 定义一个函数指针，指向目标函数
void(*real_Target)(void) = &Target;

// Detours 必要条件2: 定义一个Mine函数，用于替换目标函数
void Mine_Target(void)
{
    printf("  Mine_Target Func!\n");

    (*real_Target)();
}

//////////////////////////////////////////////////////////////////////////////
//
int main(int argc, char **argv)
{
    (void)argc;(void)argv;

    //Step1: 调用目标函数
    printf("Calling target befor Detour:\n");
    Target();
    printf("\n");

    // Step2: 使用Detour Hook 目标函数后再次调用
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)real_Target, Mine_Target);
    DetourTransactionCommit();
    printf("Detour Finshed \n");
    printf("\n");

    printf("Calling target:\n");
    Target();
    printf("\n");

    return 0;
}

