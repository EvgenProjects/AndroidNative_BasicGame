#include <android/input.h>
#include <android/asset_manager.h>
#include <GLES/gl.h>
#include <vector>

struct RGBA
{
    GLfloat red; // [0...1]
    GLfloat green; // [0...1]
    GLfloat blue; // [0...1]
    GLfloat alpha; // [0...1]
};

struct XYZ
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct XY
{
    float x;
    float y;
    XY(float x=0, float y=0) { this->x=x; this->y=y; }
};

class Graphic
{
    // constructor
    public: Graphic();

    // fields
    protected: AAssetManager* m_pAssetManager;
    protected: EGLDisplay m_Display = EGL_NO_DISPLAY;
    protected: EGLSurface m_Surface = EGL_NO_SURFACE;
    protected: EGLContext m_Context = EGL_NO_CONTEXT;
    protected: EGLConfig m_configOpenGL = nullptr;
    private:   bool m_isGraphicInited = false;
    protected: int32_t m_Width;
    protected: int32_t m_Height;

    // OpenGL private
    private: void CreateSurfaceFromWindow(ANativeWindow* pWindow);

    // OpenGL
    public: void InitGraphic(ANativeWindow* pWindow);
    public: void CloseGraphic();
    public: void DrawBackground(float red, float green, float blue, float alpha);
    public: void DrawGraphicEnd();
    int GetWidth(){ return m_Width; }
    int GetHeight(){ return m_Height; }
};

class My2DPrimitive
{
    public: void SetMode(int drawMode);
    public: void Add(float x, float y, RGBA color);
    public: void RemoveAll();
    public: void Draw();
    public: void MoveByOffset(float xOffset, float yOffset);

    // points
    protected: int m_DrawMode = 0;
    protected: std::vector<XYZ> m_arrPosition;
    protected: std::vector<RGBA> m_arrColor;
};

class My2DObject
{
    public: void Add2DPrimitive(My2DPrimitive primitive);
    public: void RemoveAll();
    public: void Draw();
    public: void MoveByOffset(float xOffset, float yOffset);

    protected: std::vector<My2DPrimitive> m_arr2DPrimitive;
    protected: XY m_posCenter;
};