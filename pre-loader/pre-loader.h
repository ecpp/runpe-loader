#pragma once
bool checkDllExists(std::string path, std::string dllName) {

    //check if exists
    if (PathFileExistsA((path + "\\" + dllName).c_str()))
        return true;
    else
        return false;

}

bool isRunningAsAdmin()
{
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;

    // Allocate and initialize a SID for the administrators group
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        // Check if the current process is a member of the administrators group
        if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
            isAdmin = FALSE;
        }

        // Free the SID
        FreeSid(adminGroup);
    }

    return isAdmin == TRUE;
}