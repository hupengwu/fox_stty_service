#include <cstdio>
#include <Settings.h>

#include <FoxSttyDataManager.h>

int main()
{

    printf("%s 向你问好!\n", "FoxSttyService");

    Settings setings;
    setings.load();

    FoxSttyDataManager data;
    data.init();
    data.exit();

    

    return 0;
}