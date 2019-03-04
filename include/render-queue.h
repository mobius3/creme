#ifndef CREME_RENDER_QUEUE_H
#define CREME_RENDER_QUEUE_H

#include <stdlib.h>
#include "render-command.h"
#include "circular-queue.h"

#ifdef __cplusplus
extern "C" {
#endif

CM_CIRQUE_DECLARE(cm_render_queue, struct cm_render_command)

#ifdef __cplusplus
}
#endif

#endif //CREME_RENDER_QUEUE_H
