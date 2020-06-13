# Dosyadan Arama Projesi
-txt, html, docx ve pdf dosyalarından aranan kelimenin tam eşleşmesini ve yakın eşleşmelerini bulur

-Yakın eşleşme için Levenshtein mesafe algoritması kullanılmıştır

-Kelimeler hash tablosuna aktarılıp tüm işlemler hash üzerinden gerçekleştirilir

-FileConverter.exe program açıldığında çalıştırılır ve docx,pdf dosyalarını docx.txt, pdf.txt dönüştürür




# Nasıl Çalışıyor?

-Dosyalardaki metinler kelime kelime ayrılır.

-Bu kelimeler hash tablomuza kelime uzunluğu baz alınarak kaydedilir

-Çakışma durumlarını azaltmak için asal sayıların kuvvetleri kullanılarak hash tablosuna ekleme yapılır.

-Asal sayıların kuvvetleri eklenecek kelime uzunluğuna göre belirlenir.

-Çakışma durumunda her kelime kendi uzunluğuna bağlı şekilde artım yapılarak ekleme işlemine devam eder.

