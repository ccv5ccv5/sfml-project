#ifndef __FOO_DRAW_H__
#define __FOO_DRAW_H__

//b2DebugDraw is DebugDraw in Box2D v2.2.1
class FooDraw : public DebugDraw {
 public:
  void DrawPolygon(b2Vec2 *vertices, int32 vertexCount, const b2Color& color) {}
  void DrawSolidPolygon(b2Vec2 *vertices, int32 vertexCount, const b2Color& color) {
    GLfloat glverts[16];
    glVertexPointer(2, GL_FLOAT, 0, glverts);
    glEnableClientState(GL_VERTEX_ARRAY);

    for(int i = 0; i < vertexCount; ++i){
      glverts[i * 2] = vertices[i].x;
      glverts[i * 2 + 1] = vertices[i].y;
    }

    glColor4f(color.r, color.g, color.b, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

    glLineWidth(3);
    glColor4f(1, 0, 1, 1);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
  }

  void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}
  void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Color& color) {}
  void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
  void DrawTransform(const b2Transform& xf) {}
};

#endif
