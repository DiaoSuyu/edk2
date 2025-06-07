#include <Uefi.h>
#include <Library/ShellCEntryLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

// #include <stdio.h>
// #include <stdlib.h>

#include "lvgl.h"
#include "lv_conf.h"
#include "lv_version.h"
#include "examples/lv_examples.h"
#include "demos/lv_demos.h"


int
main (
  IN int Argc,
  IN char **Argv
  )
{
    lv_uefi_init(gImageHandle, gST);
    lv_init();
   
    if(!lv_is_initialized()) return EFI_NOT_READY;
   
    EFI_HANDLE handle = NULL;
    lv_display_t* display = NULL;
    lv_indev_t* indev = NULL;
    lv_group_t* group = NULL;
    lv_obj_t* cursor = NULL;
    // used to get out of the main loop
    // size_t counter;
   
    // Init the display
    handle = lv_uefi_display_get_active();
    if(handle == NULL) {
        handle = lv_uefi_display_get_any();
    }
    if(handle == NULL) {
        lv_deinit();
        return EFI_UNSUPPORTED;
    }
  
   // display = lv_uefi_display_create(handle);
   // lv_display_set_default(display);
  
   // Create the group
   group = lv_group_create();
    Print(L"lvgl: 1!\n");
    lv_group_set_default(group);
    Print(L"lvgl: 2!\n");
    
    // Create an image that can be used as cursor
    // cursor = lv_image_create(lv_layer_top());
    // Print(L"lvgl: 3!\n");
    // lv_image_set_src(cursor, "E:cursor.png");
    // Print(L"lvgl: 4!\n");
    
    // Create the input devices
    indev = lv_uefi_simple_text_input_indev_create();
    Print(L"lvgl: 5!\n");
    lv_indev_set_group(indev, lv_group_get_default());
    Print(L"lvgl: 6!\n");
    lv_uefi_simple_text_input_indev_add_all(indev);
    Print(L"lvgl: 7!\n");
    
    indev = lv_uefi_simple_pointer_indev_create(NULL);
    Print(L"lvgl: 8!\n");
    lv_uefi_simple_pointer_indev_add_all(indev);
    Print(L"lvgl: 9!\n");
    // lv_indev_set_cursor(indev, cursor);
    Print(L"lvgl: 10!\n");
    
    indev = lv_uefi_absolute_pointer_indev_create(NULL);
    Print(L"lvgl: 11!\n");
    lv_uefi_absolute_pointer_indev_add_all(indev);
    Print(L"lvgl: 12!\n");
    
    lv_demo_widgets();
    Print(L"lvgl: 13!\n");
  
    // // Run main loop for ~ 10 seconds
    // counter = 0;
    // while(counter < 10000) {
    //     counter ++;
    //     gBS->Stall(1000);
    //     lv_tick_inc(1);
    //     lv_timer_handler();
    // }

    return EFI_SUCCESS;
}