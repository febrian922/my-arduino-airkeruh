# my-arduino-airkeruh
Pada penelitian ini dibangun sebuah sistem pemantauan kualitas air kolam budidaya
ikan menggunakan jaringan sensor nirkabel. Sistem terdiri atas kumpulan perangkat node sensor yang ditempatkan pada kolam untuk mengamati kualitas air dan mengirimkannya ke data center. Node sensor tersusun atas dua komponen utama yaitu mikrokontroler dan sensor Secara periodik, node sensor mengambil data pengamatan suhu dari kolam ikan. Data hasil pengamatan tersebut kemudian dikirimkan ke database lalu ke aplikasi telegram. Pada penelitian ini, peneliti memanfaatkan wemos d1r2 yang mampu mendukung komunikasi jarak jauh dengan konsumsi daya rendah. Hal ini penting mengingat node sensor akan ditempatkan pada kolam ikan sehingga node tersebut harus mampu bekerja menggunakan catu daya mandiri dari baterai yang dilengkapi sel surya. Selanjutnya, perangkat wemos d1r2 meneruskan data yang dikumpulkan dari semua node sensor ke sebuah data center untuk diolah dan dianalisis lebih lanjut. Peternak dapat mengamati kondisi air kolam budidaya secara real time dari sebuah aplikasi seperti telegram.

 Alat dan Bahan
 1. Sensor suhu DS18B20
 2. wemos d1r2
 3. Breadboard
 4. Kabel jumper
 5. Lcd monitor 16x2
 6. Relay
 7. Baterai 9V
 8. 2 Resistor
 9. LED
 10. 2 buah cangkirffff
