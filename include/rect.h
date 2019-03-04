#ifndef CREME_RECT_H
#define CREME_RECT_H

#ifdef __cplusplus
extern "C" {
#endif

struct cm_rect {
  float left, top, right, bottom;
};

extern struct cm_rect cm_rect_make(float left, float top, float right, float bottom);
extern void cm_rect_construct(struct cm_rect * rect,
                       float left, float top, float right, float bottom);
extern float cm_rect_width(struct cm_rect const * rect);
extern float cm_rect_height(struct cm_rect const * rect);

#ifdef __cplusplus
}
#endif

#endif // CREME_RECT_H