#include <lvgl.h>

#include "Scan.h"

Scan::Scan(void) {
  lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label, "--- SCAN ---");
  lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
}

Scan::~Scan(void) {
  ; // empty
}

void Scan::update(void) {
  ; // empty
}
