//////////////////////////////////////////////////////////////////////////////
//
//  Test a detour of a member function (member.cpp of member.exe)
//
//
#include <stdio.h>

#include <windows.h>
#include <detours.h>


// Ŀ�꺯��
void Target(void)
{
    printf("  Target Func! \n");
}

// Detours ��Ҫ����1: ����һ������ָ�룬ָ��Ŀ�꺯��
void(*real_Target)(void) = &Target;

// Detours ��Ҫ����2: ����һ��Mine�����������滻Ŀ�꺯��
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

    //Step1: ����Ŀ�꺯��
    printf("Calling target befor Detour:\n");
    Target();
    printf("\n");

    // Step2: ʹ��Detour Hook Ŀ�꺯�����ٴε���
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

