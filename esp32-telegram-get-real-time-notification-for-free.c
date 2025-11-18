/*
 * Course: Esp32 Telegram Get Real Time Notification For Free
 * Platform: ESP32
 * Author: Ashraf S A AlMadhoun
 * 
 * Description:
 * This code demonstrates the core concepts taught in the "Esp32 Telegram Get Real Time Notification For Free" course.
 * It provides a practical implementation that students can study, modify, and
 * use as a foundation for their own projects.
 * 
 * Learning Objectives:
 * - Understand the fundamental principles covered in this course
 * - Practice implementing the concepts with real code
 * - Build a working example that can be extended
 * 
 * Hardware Requirements:
 * - Development board (ESP32)
 * - Components as specified in CIRCUIT.md
 * - USB cable for programming
 * 
 * Pin Connections:
 * Refer to CIRCUIT.md for detailed wiring diagrams and pin assignments.
 * 
 * Usage:
 * 1. Review the code structure and comments
 * 2. Connect hardware according to CIRCUIT.md
 * 3. Upload code to your development board
 * 4. Monitor serial output for debugging
 * 
 * Course Link: https://www.udemy.com/course/esp32-telegram-get-real-time-notification-for-free/
 * Repository: https://github.com/engasm89/esp32-telegram-get-real-time-notification-for-free
 * 
 * Copyright (c) 2025 Ashraf S A AlMadhoun
 * Licensed under MIT License
 */

#include "freertos/FreeRTOS.h" // FreeRTOS
#include "freertos/task.h" // Tasks
#include "esp_log.h" // Logging
#include "esp_http_client.h" // HTTP

static const char *TAG = "TELEGRAM"; // Tag
static int backoff_ms = 2000; // Backoff for retry

void app_main(void) { // Program entry point
  // Placeholder: use Telegram Bot API to send a message via HTTP
  // Avoid hardcoding secrets; store tokens securely
  esp_http_client_config_t cfg = { .url = "https://api.telegram.org/bot<TOKEN>/sendMessage" }; // Endpoint
  esp_http_client_handle_t client = esp_http_client_init(&cfg); // Init
  const char *payload = "chat_id=<CHAT>&text=Hello"; // Example body
  while (true) { // Loop
    esp_http_client_set_method(client, HTTP_METHOD_POST); // POST
    esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded"); // Header
    esp_http_client_set_post_field(client, payload, strlen(payload)); // Body
    if (esp_http_client_perform(client) == ESP_OK) { // Perform
      ESP_LOGI(TAG, "Telegram POST status=%d", esp_http_client_get_status_code(client)); // Log
      backoff_ms = 2000; // Reset backoff
      vTaskDelay(pdMS_TO_TICKS(10000)); // 10s interval
    } else { // Error
      ESP_LOGW(TAG, "Telegram request failed, backoff=%dms", backoff_ms); // Warn
      vTaskDelay(pdMS_TO_TICKS(backoff_ms)); // Backoff delay
      backoff_ms = backoff_ms < 60000 ? backoff_ms * 2 : 60000; // Exponential backoff
    } // End if
  } // End loop
} // End of main function

