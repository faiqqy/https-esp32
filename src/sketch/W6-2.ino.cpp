#include <Arduino.h>
#line 1 "C:\\Users\\user\\dev\\Iot\\pelatihan\\w6\\W6-2\\W6-2.ino"
#include <WiFi.h>
#include <WiFiClientSecure.h>

//wifi ssid and pass
#define SSID "Wokwi-GUEST"
#define PASS ""

#define SERVER_NAME "phet-dev.colorado.edu"
#define PORT 443

#define CERT \
"-----BEGIN CERTIFICATE-----\n" \
"MIIG6jCCBdKgAwIBAgIRAPZVtInxNI6mH26T/3M2Y2EwDQYJKoZIhvcNAQELBQAw\n" \
"gZUxCzAJBgNVBAYTAkdCMRswGQYDVQQIExJHcmVhdGVyIE1hbmNoZXN0ZXIxEDAO\n" \
"BgNVBAcTB1NhbGZvcmQxGDAWBgNVBAoTD1NlY3RpZ28gTGltaXRlZDE9MDsGA1UE\n" \
"AxM0U2VjdGlnbyBSU0EgT3JnYW5pemF0aW9uIFZhbGlkYXRpb24gU2VjdXJlIFNl\n" \
"cnZlciBDQTAeFw0yNTAyMDMwMDAwMDBaFw0yNjAzMDYyMzU5NTlaMGwxCzAJBgNV\n" \
"BAYTAlVTMREwDwYDVQQIEwhDb2xvcmFkbzEqMCgGA1UEChMhVW5pdmVyc2l0eSBv\n" \
"ZiBDb2xvcmFkbyBhdCBCb3VsZGVyMR4wHAYDVQQDExVwaGV0LWRldi5jb2xvcmFk\n" \
"by5lZHUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCnJh1DIHlPPgNj\n" \
"IWNmKCIZrGK35yYI/ocG1wpbYtdWpKZ6J0sYG+T2dv9n2YkgXB/5YGZCH8PoT20V\n" \
"OvCiA2wrtdRVMEgDvj1RljVq9s4xuFrFcNcjWMFfd5Mg5hUTz67VKnSO3sQ2vvyE\n" \
"2IBohNEOKXBo53nRZ8/txyyO5HtiZS+GPpmLgrOxzheSeUgJOBnTCaWP4BeC5zEW\n" \
"nS+BzGJ74rttMfWkS01yj5RksjoSx/nvcvKiqrQW+/lA7n2giJDSgIvWanhAuIL+\n" \
"jgm/0OStjkhB7ApA/Wacwn5LdpiS4TiI5K8pQ1MCfDn4fCjvtjRd+iJwd/6hp8Am\n" \
"T72kEfvtAgMBAAGjggNbMIIDVzAfBgNVHSMEGDAWgBQX2dYlJ2f5McJJQ9kwNkSM\n" \
"bKlP6zAdBgNVHQ4EFgQUMv1i4tjk7pZJJhIsFtUE3uPEAGIwDgYDVR0PAQH/BAQD\n" \
"AgWgMAwGA1UdEwEB/wQCMAAwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMC\n" \
"MEoGA1UdIARDMEEwNQYMKwYBBAGyMQECAQMEMCUwIwYIKwYBBQUHAgEWF2h0dHBz\n" \
"Oi8vc2VjdGlnby5jb20vQ1BTMAgGBmeBDAECAjBaBgNVHR8EUzBRME+gTaBLhklo\n" \
"dHRwOi8vY3JsLnNlY3RpZ28uY29tL1NlY3RpZ29SU0FPcmdhbml6YXRpb25WYWxp\n" \
"ZGF0aW9uU2VjdXJlU2VydmVyQ0EuY3JsMIGKBggrBgEFBQcBAQR+MHwwVQYIKwYB\n" \
"BQUHMAKGSWh0dHA6Ly9jcnQuc2VjdGlnby5jb20vU2VjdGlnb1JTQU9yZ2FuaXph\n" \
"dGlvblZhbGlkYXRpb25TZWN1cmVTZXJ2ZXJDQS5jcnQwIwYIKwYBBQUHMAGGF2h0\n" \
"dHA6Ly9vY3NwLnNlY3RpZ28uY29tMIIBfwYKKwYBBAHWeQIEAgSCAW8EggFrAWkA\n" \
"dgCWl2S/VViXrfdDh2g3CEJ36fA61fak8zZuRqQ/D8qpxgAAAZTNis1qAAAEAwBH\n" \
"MEUCICz2+ytEypGOe6M1Yuyv7wyRqonb8zrRXobCD93EWpczAiEA8ThnXnDH5EMy\n" \
"oBdn4qbQLT9iQYk8Ld6nMGQksIBEI2YAdgAZhtTHKKpv/roDb3gqTQGRqs4tcjEP\n" \
"rs5dcEEtJUzH1AAAAZTNisz6AAAEAwBHMEUCICJ85EWxIIlXTKndhQPVk1cqM4Mh\n" \
"i/jGlxqZjTi+jySbAiEAxFfCIyCoPJ+envxjqw6HwFXk7eoSTRVlq4uI5NtFRnYA\n" \
"dwDLOPcViXyEoURfW8Hd+8lu8ppZzUcKaQWFsMsUwxRY5wAAAZTNis0uAAAEAwBI\n" \
"MEYCIQCkOcdEiax3Q1bfrXfz6Nj1GyGFBXxwFF9XOK0Q/EEw9wIhAOyw73VuZ2Vl\n" \
"ZbPqUCzmATgcuE2ftcGTJxEZEYOQZmn9MCAGA1UdEQQZMBeCFXBoZXQtZGV2LmNv\n" \
"bG9yYWRvLmVkdTANBgkqhkiG9w0BAQsFAAOCAQEACGM/J8HFXNrlJLkXeT2EW9z9\n" \
"2FGLQSo3dywTbN781AL9RlOZu1lE4xg2dKhMT2KdwgQBR9YmUSSzgdt83FkLcRmU\n" \
"uZ34aF4ExRIaXeFS61WuGd83+Uy9DHH2NglkwaW1zD5SvqazGRVnO39Q9O55TBvu\n" \
"8UivzcSnO/31zXfuik0ORJETBTLHgvYOE3r5ch6mCcAaBPiR846PlYifBrOkm6uo\n" \
"cYD2njnaMRJJKLzZXvTJHFG+aOZ3b0IyL4YFHPPes/JI2Hgo8d0qwBXIiA/fhTpl\n" \
"35AeUD6NYMe9A0vVi9S8zZCNghRo/ztXyrbhbBH30iEDIBpY6xwjm+foskgMKw==\n" \
"-----END CERTIFICATE-----\n"


WiFiClientSecure client;

#line 55 "C:\\Users\\user\\dev\\Iot\\pelatihan\\w6\\W6-2\\W6-2.ino"
void setup();
#line 89 "C:\\Users\\user\\dev\\Iot\\pelatihan\\w6\\W6-2\\W6-2.ino"
void loop();
#line 55 "C:\\Users\\user\\dev\\Iot\\pelatihan\\w6\\W6-2\\W6-2.ino"
void setup() {

//init Serial
  Serial.begin(115200);                                         
  while( !Serial );

//init wifi
  Serial.println("connect");
  Serial.println("Mencoba terhubung ke ASPROSENA");
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
  }
  Serial.println();
  Serial.println("berhasil nyambung");

  client.setCACert(CERT);

  client.setPlainStart();

    if (!client.connect(SERVER_NAME, PORT)){
      Serial.print("gak bisa nyambung ke url");

    }else {
      client.println("GET /html/build-an-atom/0.0.0-3/simple-text-only-test-page.html HTTP/1.1");
      client.println("Host: phet-dev.colorado.edu");
      client.println("Accept: */*");
//      client.println("User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:137.0) Gecko/20100101 Firefox/137.0");
      client.println();

    }

}

void loop() {

  if (client.available()){
    char c = client.read();
    Serial.print(c);
  }

  
}

