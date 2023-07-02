# Risetsawah Project

## Overview
Proyek risetsawah adalah sebuah penelitian yang bertujuan untuk memonitor dan menganalisis kondisi tanah sawah menggunakan mikrokontroler Arduino Mega dan ESP8266. Pada penelitian ini, beberapa sensor digunakan untuk mendeteksi nilai kelembaban, suhu, pH, dan warna tanah berdasarkan nilai R, G, dan B.

Data yang dikumpulkan oleh sensor-sensor tersebut akan dikirim ke platform Internet of Things (IoT) yaitu Thingspeak. Dashboard pada Thingspeak akan menampilkan data secara grafis sehingga pengguna dapat memantau kondisi tanah sawah secara real-time.

## Komponen yang Digunakan
- Arduino Mega
- ESP8266
- Sensor DS18B20 (untuk mendeteksi suhu)
- Soil Moisture Sensor (untuk mendeteksi kelembaban tanah)
- pH Probe (untuk mendeteksi nilai pH tanah)
- TCS3200 (untuk mendeteksi warna tanah)
![Desain Alat]images/WiringDesain.png

## Penjelasan Kode Sumber
- `Get-Data-Set.ino`: Kode sumber utama yang berisi konfigurasi dan logika pembacaan data dari sensor.
- `Send-Data.ino`: Kode yang berisi konfigurasi data untuk api Thingspeak dan logika pembacaan data dari sensor serta pengiriman data ke Thingspeak.
- `DS18B20.h`: Library untuk sensor suhu DS18B20. 
- `SoilMoistureSensor.h`: Library untuk sensor kelembaban tanah.
- `pHProbe.h`: Library untuk sensor pH tanah.
- `TCS3200.h`: Library untuk sensor warna TCS3200.

## Konfigurasi Thingspeak
1. Buat akun Thingspeak di [https://thingspeak.com](https://thingspeak.com).
2. Buat channel baru dan sesuaikan jumlah field dengan sensor yang digunakan.
3. Dapatkan Write API Key dari channel tersebut.
4. Update nilai `THINGSPEAK_API_KEY` pada kode sumber `main.ino` dengan Write API Key yang didapatkan.

## Penggunaan
1. Hubungkan Arduino Mega dan ESP8266.
2. Sambungkan sensor-sensor ke pin yang sesuai pada Arduino Mega.
3. Pasang program menggunakan Arduino IDE.
4. Periksa koneksi Wi-Fi pada ESP8266 dan pastikan dapat terhubung ke internet.
5. Akses dashboard pada Thingspeak untuk melihat data yang dikirimkan oleh sensor.
![Output Thingspeak]images/OutputThinhspeak.png
## Lisensi
Proyek ini dilisensikan di bawah [MIT License](LICENSE).

