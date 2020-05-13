package ind.tmxdev.nativeandroid;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.Log;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class NativeRenderer implements GLSurfaceView.Renderer {

    private int id = -1;
    private String vertexShader = "precision highp float;\n" +
            "\n" +
            "attribute vec4 _position;\n" +
            "void main() {\n" +
            "    gl_Position = _position;\n" +
            "}";
    private String fragmentShader = "precision mediump float;\n" +
            "\n" +
            "uniform vec4 _color;\n" +
            "\n" +
            "void main()\n" +
            "{\n" +
            "    gl_FragColor = _color;\n" +
            "}";

    static {
        System.loadLibrary("native-lib");
    }

    private native void onCreated(int id);
    private native void onChanged(int id, int width, int height);
    private native void onDraw(int id);

    private native void loadVertexShader(int id, String shader);
    private native void loadFragmentShader(int id, String shader);
    private native void initShader(int id);

    private native int getProgram(int id);

    public void readShaders(Context context) {

    }

    public NativeRenderer(int id) {
        this.id = id;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        loadVertexShader(id, vertexShader);
        loadFragmentShader(id, fragmentShader);
        onCreated(id);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        onChanged(id, width, height);
    }



    @Override
    public void onDrawFrame(GL10 gl) {
        long t = System.currentTimeMillis();
        onDraw(id);
        Log.d("OPENGL_DEBUG","Measure for native: " + (System.currentTimeMillis() - t));


        int progID = getProgram(id);
        t = System.currentTimeMillis();

        GLES20.glUseProgram(progID);
        int colorLoc = GLES20.glGetUniformLocation(progID,"_color");
        int posLoc = GLES20.glGetAttribLocation(progID,"_position");
        float[] verts = new float[]{-0.5F, 0.0F, 0.0F, 1.0F, 0.0F, 0.5F, 0.0F, 1.0F, 0.5F, 0.0F, 0.0F, 1.0F};
        float[] color = new float[]{0.0F, 0.0F, 0.0F, 1.0F};
        FloatBuffer model = ByteBuffer.allocateDirect(verts.length * 4).order(ByteOrder.nativeOrder()).asFloatBuffer();
        model.put(verts);
        model.position(0);
        GLES20.glEnableVertexAttribArray(posLoc);
        for(int i = 0; i < 60; i++) {
            GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);
            GLES20.glUniform4fv(colorLoc,1,color,0);
            for (int j = 0; j < 1000; j++) {
                GLES20.glVertexAttribPointer(posLoc,4,GLES20.GL_FLOAT,false,0,model);
                model.position(0);
                GLES20.glDrawArrays(GLES20.GL_TRIANGLES,0,3);
            }
        }

        Log.d("OPENGL_DEBUG","Measure for java: " + (System.currentTimeMillis() - t));
    }

}
