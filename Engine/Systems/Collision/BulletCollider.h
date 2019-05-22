#ifndef BULLETCOLLIDER_H
#define BULLETCOLLIDER_H

#include "Core/Interfaces/Object.h"

#include <bullet/BulletCollision/CollisionShapes/btCollisionShape.h>
#include <glm/vec3.hpp>

#include "Core/Resources/Resource.h"
#include "Mesh/Model.h"
#include "SceneGraph/Transform.h"

class ENGINE_API BulletCollider : public Object
{
protected:
	btCollisionShape* _collisionShape;
	glm::vec3 _offset;
	Resource<Model> _mesh;

	bool _isDirty;

public:
	BulletCollider ();
	virtual ~BulletCollider ();

	void SetMesh (const Resource<Model>& model);
	void SetOffset (const glm::vec3& offset);
	void SetDirty (bool isDirty);

	btCollisionShape* GetCollisionShape () const;
	glm::vec3 GetOffset () const;
	Resource<Model> GetMesh () const;
	bool IsDirty () const;
protected:
	virtual void Rebuild () = 0;

	void DestroyCollisionShape ();
};

#endif