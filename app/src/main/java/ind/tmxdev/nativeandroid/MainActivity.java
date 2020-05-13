package ind.tmxdev.nativeandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private native void freeGraphics();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        NativeRenderer renderer = new NativeRenderer(1);
        NativeSurface surf = new NativeSurface(this);
        surf.setEGLContextClientVersion(2);
        surf.setRenderer(renderer);

        setContentView(surf);

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        freeGraphics();
    }
}
