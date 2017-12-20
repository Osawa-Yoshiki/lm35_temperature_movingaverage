#define TEMP_PIN A0
#define MEAN 100

//移動平均用
int cnt = 0;
float temp[MEAN+1] = {};
boolean calibration_done = false;

//温度の取得
float get_temp() {
    int analogValue = analogRead(TEMP_PIN);
    float temp = ((analogValue * 5) / 1024.0) * 100;
    return temp;
}

void setup () {
  Serial.begin(9600);                       //ボーレート9600でシリアル通信開始
  Serial.println("hello, Arduino!");      //シリアルポートにメッセージ出力
}

void loop () {
  if (temp[MEAN-1] != 0.00) {               //最初の100回分、取得が終わったか判定
    calibration_done = true;
    }
  float sum = 0.0;

  if (cnt == MEAN) {                        //カウンタをループさせる
    cnt = 0;
  }
  temp[cnt] = get_temp();                   //配列の要素cntを最新値で上書きする
    cnt++;

  for (int i = 0; i < MEAN;i++) {           //配列の要素をすべて合計
        sum += temp[i];
  }
    float celsius = sum / MEAN;             //平均を求める

  if (calibration_done == true) {                           //最初の取得が終わっていればクラウド送信（未実装）
        if (cnt % 10 == 0) {                                //出力を10回に1回に制限
            Serial.print("Degree(C):   ");               //温度をシリアルに出力（表示用）
            Serial.println(celsius);                       //温度をシリアルに出力
              //requestURI(celsius);                         //温度をクラウドに送信（未実装）
    }
    } else {
        Serial.println("calibrating... Please Wait");    //最初の取得中は表示も送信もしない
    }
  delay(100);
}
