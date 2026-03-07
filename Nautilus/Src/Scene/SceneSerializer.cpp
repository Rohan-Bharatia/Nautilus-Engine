#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#ifndef _SCENE_SCENE_SERIALIZER_CPP_
    #define _SCENE_SCENE_SERIALIZER_CPP_

#include "SceneSerializer.h"

#include "Components.h"
#include "Entity.h"
#include "Core/IO.h"

namespace YAML
{
    template<>
    struct convert<Nt::String>
    {
        static Node encode(const Nt::String& rhs)
        {
            Node node;
            node.push_back((const char*)rhs);
            return node;
        }

        static bool decode(const Node& node, Nt::String& rhs)
        {
            if (!node.IsSequence() || node.size() != 1)
                return false;
            rhs = Nt::String(node[0].as<std::string>().c_str());
            return true;
        }
    };

    template<>
    struct convert<Nt::UUID>
    {
        static Node encode(const Nt::UUID& rhs)
        {
            Node node;
            node.push_back((Nt::uint64)rhs);
            return node;
        }

        static bool decode(const Node& node, Nt::UUID& rhs)
        {
            if (!node.IsSequence() || node.size() != 1)
                return false;
            rhs = Nt::UUID(node[0].as<Nt::uint64>());
            return true;
        }
    };

    template<>
    struct convert<Nt::Vector2>
    {
        static Node encode(const Nt::Vector2& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, Nt::Vector2& rhs)
        {
            if (!node.IsSequence() || node.size() != 2)
                return false;
            rhs.x = node[0].as<Nt::float32>();
            rhs.y = node[1].as<Nt::float32>();
            return true;
        }
    };

    template<>
    struct convert<Nt::Vector3>
    {
        static Node encode(const Nt::Vector3& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, Nt::Vector3& rhs)
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;
            rhs.x = node[0].as<Nt::float32>();
            rhs.y = node[1].as<Nt::float32>();
            rhs.z = node[2].as<Nt::float32>();
            return true;
        }
    };

    template<>
    struct convert<Nt::Vector4>
    {
        static Node encode(const Nt::Vector4& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, Nt::Vector4& rhs)
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;
            rhs.x = node[0].as<Nt::float32>();
            rhs.y = node[1].as<Nt::float32>();
            rhs.z = node[2].as<Nt::float32>();
            rhs.w = node[3].as<Nt::float32>();
            return true;
        }
    };

    // template<>
    // struct convert<Nt::Color>
    // {
    //     static Node encode(const Nt::Color& rhs)
    //     {
    //         Node node;
    //         node.push_back(rhs.r);
    //         node.push_back(rhs.g);
    //         node.push_back(rhs.b);
    //         node.push_back(rhs.a);
    //         return node;
    //     }

    //     static bool decode(const Node& node, Nt::Color& rhs)
    //     {
    //         if (!node.IsSequence() || node.size() != 4)
    //             return false;
    //         rhs.r = node[0].as<Nt::float32>();
    //         rhs.g = node[1].as<Nt::float32>();
    //         rhs.b = node[2].as<Nt::float32>();
    //         rhs.a = node[3].as<Nt::float32>();
    //         return true;
    //     }
    // };
} // namespace YAML

namespace Nt
{
    YAML::Emitter& operator<<(YAML::Emitter& out, const String& string)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << (const char*)string << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const UUID& uuid)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << (uint64)uuid << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const Vector2& vec)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << vec.x << vec.y << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const Vector3& vec)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << vec.x << vec.y << vec.z << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const Vector4& vec)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << vec.x << vec.y << vec.z << vec.w << YAML::EndSeq;
        return out;
    }

    // YAML::Emitter& operator<<(YAML::Emitter& out, const Color& col)
    // {
    //     out << YAML::Flow;
    //     out << YAML::BeginSeq << col.r << col.g << col.b << col.a << YAML::EndSeq;
    //     return out;
    // }

    SceneSerializer::SceneSerializer(const Ref<Scene>& scene) :
        m_scene(scene)
    {}

    void SceneSerializer::Serialize(const String& filepath)
    {
        NT_CORE_INFO("Saving scene %s", "Untitled");
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << "Untitled";
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        m_scene->GetRegistry().view<IDComponent>().each([&](auto entityId, auto&)
        {
            Entity entity(entityId, m_scene.get());
            if (!entity)
                return;

            out << YAML::BeginMap;
            if (entity.HasComponent<IDComponent>())
                out << YAML::Key << "Entity" << YAML::Value << entity.GetUUID();

            out << YAML::EndMap;

            if (entity.HasComponent<TagComponent>())
            {
                out << YAML::Key << "TagComponent";
                out << YAML::BeginMap;
                out << YAML::Key << "Tag" << YAML::Value << entity.GetName();
                out << YAML::EndMap;
            }

            if (entity.HasComponent<TransformComponent>())
            {
                out << YAML::Key << "TransformComponent";
                out << YAML::BeginMap;

                auto& tc = entity.GetComponent<TransformComponent>();
                out << YAML::Key << "Translation" << YAML::Value << tc.position;
                out << YAML::Key << "Rotation" << YAML::Value << tc.rotation;
                out << YAML::Key << "Scale" << YAML::Value << tc.scale;
                out << YAML::Key << "LockZAxis" << YAML::Value << tc.lockZAxis;

                out << YAML::EndMap;
            }

            if (entity.HasComponent<CameraComponent>())
            {
                out << YAML::Key << "CameraComponent";
                out << YAML::BeginMap;

                auto& cc = entity.GetComponent<CameraComponent>();
                out << YAML::Key << "ProjectionType" << YAML::Value << (uint32)cc.camera->GetCameraType();
                out << YAML::Key << "OrthographicSize" << YAML::Value << cc.camera->GetOrthographicSize();
                out << YAML::Key << "OrthographicNear" << YAML::Value << cc.camera->GetOrthographicNear();
                out << YAML::Key << "OrthographicFar" << YAML::Value << cc.camera->GetOrthographicFar();
                out << YAML::Key << "PerspectiveFOV" << YAML::Value << cc.camera->GetPerspectiveFOV();
                out << YAML::Key << "PerspectiveNear" << YAML::Value << cc.camera->GetPerspectiveNear();
                out << YAML::Key << "PerspectiveFar" << YAML::Value << cc.camera->GetPerspectiveFar();
                out << YAML::Key << "Primary" << YAML::Value << cc.primary;
                out << YAML::Key << "FixedRatio" << YAML::Value << cc.fixedRatio;

                out << YAML::EndMap;
            }

            if (entity.HasComponent<SpriteComponent>())
            {
                out << YAML::Key << "SpriteComponent";
                out << YAML::BeginMap;

                auto& sc = entity.GetComponent<SpriteComponent>();
                out << YAML::Key << "Color" << YAML::Value << sc.color;
                out << YAML::Key << "Texture" << YAML::Value << sc.texture->GetTexture()->GetRenderId();
                out << YAML::Key << "TilingFactor" << YAML::Value << sc.tilingFactor;

                out << YAML::EndMap;
            }

            if (entity.HasComponent<NativeScriptComponent>())
            {
                out << YAML::Key << "NativeScriptComponent";
                out << YAML::BeginMap;

                auto& nsc = entity.GetComponent<NativeScriptComponent>();
                out << YAML::Key << "ClassName" << YAML::Value << nsc.className;
            }
        });
        out << YAML::EndSeq << YAML::EndMap;

        WriteFile(filepath, String(out.c_str()), true);
    }

    void SceneSerializer::SerializeRuntime(const String& filepath)
    {
        NT_ASSERT(false, "Not implemented");
    }

    bool SceneSerializer::Deserialize(const String& filepath)
    {
        YAML::Node data;
        try
        {
            data = YAML::LoadFile((const char*)filepath);
        }
        catch (YAML::ParserException e)
        {
            NT_CORE_ERROR("Failed to load %s", (const char*)filepath);
            return false;
        }

        if (!data["Scene"])
            return false;

        String name = data["Scene"].as<String>();
        NT_CORE_INFO("Loading scene %s", (const char*)name);

        auto entities = data["Entities"];
        if (entities)
        {
            for (auto entity : entities)
            {
                    UUID uuid                 = entity["Entity"].as<UUID>();
                    String name               = entity["TagComponent"]["Tag"].as<String>();
                    Entity deserializedEntity = m_scene->CreateEntity(uuid, name);

                    auto transformComponent = entity["TransformComponent"];
                    if (transformComponent)
                    {
                        auto& tc     = deserializedEntity.GetComponent<TransformComponent>();
                        tc.position  = transformComponent["Translation"].as<Vector3>();
                        tc.rotation  = transformComponent["Rotation"].as<Vector3>();
                        tc.scale     = transformComponent["Scale"].as<Vector3>();
                        tc.lockZAxis = transformComponent["LockZAxis"].as<bool>();
                    }

                    auto cameraComponent = entity["CameraComponent"];
                    if (cameraComponent)
                    {
                        auto& cc      = deserializedEntity.GetComponent<CameraComponent>();
                        cc.camera->SetCameraType((CameraType)cameraComponent["ProjectionType"].as<uint32>());
                        cc.camera->SetOrthographicSize(cameraComponent["OrthographicSize"].as<float32>());
                        cc.camera->SetOrthographicNear(cameraComponent["OrthographicNear"].as<float32>());
                        cc.camera->SetOrthographicFar(cameraComponent["OrthographicFar"].as<float32>());
                        cc.camera->SetPerspectiveFOV(cameraComponent["PerspectiveFOV"].as<float32>());
                        cc.camera->SetPerspectiveNear(cameraComponent["PerspectiveNear"].as<float32>());
                        cc.camera->SetPerspectiveFar(cameraComponent["PerspectiveFar"].as<float32>());
                        cc.primary    = cameraComponent["Primary"].as<bool>();
                        cc.fixedRatio = cameraComponent["FixedRatio"].as<bool>();
                    }

                    auto spriteComponent = entity["SpriteComponent"];
                    if (spriteComponent)
                    {
                        auto& sc        = deserializedEntity.GetComponent<SpriteComponent>();
                        sc.color        = spriteComponent["Color"].as<Color>();
                        // sc.texture      = CreateRef<Texture2D>(spriteComponent["Texture"].as<uint32>());
                        sc.tilingFactor = spriteComponent["TilingFactor"].as<float32>();
                    }

                    auto nativeScriptComponent = entity["NativeScriptComponent"];
                    if (nativeScriptComponent)
                    {
                        auto& nsc     = deserializedEntity.GetComponent<NativeScriptComponent>();
                        nsc.className = nativeScriptComponent["ClassName"].as<String>();
                    }
                }
        }

        return true;
    }

    bool SceneSerializer::DeserializeRuntime(const String& filepath)
    {
        NT_ASSERT(false, "Not implemented");
        return false;
    }
} // namespace Nt

#endif // _SCENE_SCENE_SERIALIZER_CPP_
