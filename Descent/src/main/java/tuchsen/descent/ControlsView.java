package tuchsen.descent;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.View;

/**
 * Created by devin on 4/19/16.
 */
public class ControlsView extends View {
    public ControlsView(Context context) {
        super(context);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        Paint light = new Paint();
        canvas.drawRect(50, 50, 100, 100, light);
    }
}
