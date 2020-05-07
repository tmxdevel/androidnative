package ind.tmxdev.nativeandroid;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class NativeRenderer implements GLSurfaceView.Renderer {

    private int id = -1;
    private String vertexShader = "";
    private String fragmentShader = "";

    static {
        System.loadLibrary("native-lib");
    }

    private native void onCreated(int id);
    private native void onChanged(int id, int width, int height);
    private native void onDraw(int id);

    private native void loadVertexShader(int id, String shader);
    private native void loadFragmentShader(int id, String shader);
    private native void initShader(int id);

    public void readShaders(Context context) {

    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        onCreated(id);
        loadVertexShader(id, vertexShader);
        loadFragmentShader(id, fragmentShader);
        initShader(id);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        onChanged(id, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        onDraw(id);
    }

}
