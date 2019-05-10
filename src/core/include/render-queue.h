#ifndef CREME_RENDER_QUEUE_H
#define CREME_RENDER_QUEUE_H

#include <stdlib.h>
#include "render-command.h"
#include "circular-queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A render queue is a circular queue containing render commands. You should
 * use it to pass to widget rendering functions and you should read from it
 * when rendering them.
 *
 * @sa cm_render_command
 */

CM_CIRQUE_DECLARE(cm_render_queue, struct cm_render_command)

#ifdef __cplusplus
}
#endif

#endif /* CREME_RENDER_QUEUE_H */
