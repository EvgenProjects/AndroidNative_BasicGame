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
    XYZ(float x=0, float y=0, float z=0) { this->x=x; this->y=y; this->z=z;}
};

struct XY
{
    float x;
    float y;
    XY(float x=0, float y=0) { this->x=x; this->y=y; }
};


struct XYZ_RGBA
{
    XYZ position;
    RGBA color;
    XYZ_RGBA(XY pos, RGBA color, GLfloat z=0) { this->position.x=pos.x; this->position.y=pos.y; this->position.z=z; this->color=color; }
    XYZ_RGBA(XYZ position, RGBA color) { this->position=position; this->color=color; }
};

class MyGraphic
{
    // constructor
    public: MyGraphic();

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

class MyPolygon
{
    public: MyPolygon();
    public: MyPolygon(int drawMode, std::vector<XYZ_RGBA> arrPoint);

    public: void Draw();
    public: void MoveByOffset(float xOffset, float yOffset);
    public: int ItemsCount() {return m_arrPositionColor.size();}
    public: XYZ_RGBA& GetItem(int i) {return m_arrPositionColor[i];}

    // points
    protected: int m_DrawMode;
    protected: std::vector<XYZ_RGBA> m_arrPositionColor;
};

class MyObject
{
    public: MyObject();
    public: MyObject(std::vector<MyPolygon> arrPolygon);

    public: void Draw();
    public: void MoveByOffset(float xOffset, float yOffset);
    public: void CreateByTemplate(const MyObject& objTemplate, XY realPos, float realWidth, float realHeight);

    protected: std::vector<MyPolygon> m_arrPolygon;
};