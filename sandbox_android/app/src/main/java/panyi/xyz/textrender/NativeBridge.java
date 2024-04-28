package panyi.xyz.textrender;

import android.content.res.AssetManager;

public final class NativeBridge {
    static {
        System.loadLibrary("purple");
    }

    public static native void init();

    public static native void tick();

    public static native void free();

    public static native void resize(int width , int height);

    public static native void setAndroidAssetManager(AssetManager mgr);

    public static native void handleOnAction(int action , float x , float y);
}
