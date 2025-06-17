#include "PositionTask.h"
#include "Queues.h"
#include "PositionEstimator.h"

void PositionTask(void* pv) {
  PositionEstimator pe;
  pe.begin();
  float pct;
  for (;;) {
    pct = pe.getPositionPercent();
    xQueueOverwrite(positionQueue, &pct);
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}
