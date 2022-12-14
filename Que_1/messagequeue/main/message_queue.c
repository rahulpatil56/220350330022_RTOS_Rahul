#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

#define QueueLength 4      
#define ItemSize 16       

TaskHandle_t task1handle, task2handle, task3handle, task4handle, task5handle;
QueueHandle_t q_t4_t5;

void task1 (void *data)
{
    while(1)
    {
        printf("\n Task1\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task2 (void *data)
{
    while(1)
    {
        printf("\n Task2\n");
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task3 (void *data)
{
    while(1)
    {
        printf("\n Task3\n");
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task4 (void *data)
{
    Basetype_t send;
    int pdata = 100;

    while(1)
    {
        pdata++;
        printf("\n Task4 \n");
        send = xQueueSend(q_t4_t5, &pdata, pdMS_TO_TICKs(1000));
        if(send == pdFALSE)
        {
            printf("sending failed\n");
        }
        else
        {
            printf("data Sent to Task5\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
    vTaskDelete(NULL);
}

void task5 (void *data)
{
    int buffer;
    BaseType_t rec =0;
    while(1)
    { 
        printf("\n Task5 \n");
        rec = xQueueReceive(q_t4_t5, &buffer, pdMS_TO_TICKS(1000));
        if(rec == pdTRUE)
        {
            printf("Data Received from Task4: %d\n", buffer);
        }                       
        else
        {
            perror("Error in Receving Data From Task4 \n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    BaseType_t res;
    printf("Starting Main Task \n");

    q_t4_t5 = xQueueCreate(QueueLength, ItemSize);

    // Create Task 1
    res = xTaskCreate(task1, "Task1", 2048, NULL, 5, &task1Handle);
    if (res != pdPASS)
    {
        perror("Error in Creating Task1\n");
    }
    else
    {
        printf("Task1 Created\n");
    }

    // Create Task 2
    res = xTaskCreate(task2, "Task2", 2048, NULL, 6, &task1Handle);
    if (res != pdPASS)
    {
        perror("Error in Creating Task2\n");
    }
    else
    {
        printf("Task2 Created\n");
    }

    // Create Task 3
    res = xTaskCreate(task3, "Task3", 2048, NULL, 7, &task1Handle);
    if (res != pdPASS)
    {
        perror("Error in Creating Task3\n");
    }
    else
    {
        printf("Task3 Created\n");
    }

    // Create Task 4
    res = xTaskCreate(task4, "Task4", 2048, NULL, 8, &task1Handle);
    if (res != pdPASS)
    {
        perror("Error in Creating Task4\n");
    }
    else
    {
        printf("Task4 Created\n");
    }

    // Create Task 5
    res = xTaskCreate(task5, "Task5", 2048, NULL, 9, &task1Handle);
    if (res != pdPASS)
    {
        perror("Error in Creating Task5\n");
    }
    else
    {
        printf("Task5 Created\n");
    }
}
        
