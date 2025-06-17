#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "Types.h"

extern QueueHandle_t regQueue;
extern QueueHandle_t cmdQueue;
extern QueueHandle_t logQueue;
extern QueueHandle_t stateQueue;
extern QueueHandle_t positionQueue;
