package com.example.cameratest;



import android.content.Context; 
import android.graphics.Canvas; 
import android.graphics.Color; 
import android.graphics.Paint; 
import android.view.View; 

public class CameraOnView extends View { 
     public CameraOnView(Context context) { 
     super(context); 
     } 
     protected void onDraw(Canvas c) { 

     Paint p = new Paint(); 
     int cw = getWidth()/2;
     int ch = getHeight()/2 - 200;
     
     p.setColor(Color.RED); 
     p.setStrokeWidth(5);
  //   c.drawRect(200, 400, 300, 500, p); 
     c.drawLine(cw-256, ch-256, cw+256, ch-256, p);
     c.drawLine(cw-256, ch-256, cw-256, ch+256, p);
     c.drawLine(cw+256, ch-256, cw+256, ch+256, p);
     c.drawLine(cw-256, ch+256, cw+256, ch+256, p);
     } 
} 