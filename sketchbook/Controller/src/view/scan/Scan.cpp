#include "Scan.h"

Scan::Scan(void):
  _screen(lv_obj_create(NULL, NULL)) {
  ; // empty
}

Scan::Scan(const uint16_t width, const uint16_t height):
  Scan() {

  lv_obj_set_pos(_screen, 0, 0);
  lv_obj_set_size(_screen, width, height);

  lv_obj_t *label = lv_label_create(_screen, NULL);
  lv_label_set_text(label, "--- SCAN ---");
  lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
}

Scan::~Scan(void) {
  lv_obj_del(_screen);
}

void Scan::update(void) {
  ; // empty
}

void Scan::show(void) {
  if (nullptr != _screen) {
    lv_scr_load(_screen);
  }
}
