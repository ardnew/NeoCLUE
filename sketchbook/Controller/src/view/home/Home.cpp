#include <lvgl.h>

#include "Home.h"

Home::Home(void) {
  lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label, "--- HOME ---");
  lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
}

Home::~Home(void) {
  ; // empty
}

void Home::update(void) {
  ; // empty
}
