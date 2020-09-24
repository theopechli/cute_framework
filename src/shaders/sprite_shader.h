#pragma once
/*
    #version:1# (machine generated, don't edit!)

    Generated by sokol-shdc (https://github.com/floooh/sokol-tools)

    Overview:

        Shader program 'shd':
            Get shader desc: sprite_default_shd_shader_desc()
            Vertex shader: vs
                Attribute slots:
                    ATTR_sprite_default_vs_in_pos = 0
                    ATTR_sprite_default_vs_in_uv = 1
                    ATTR_sprite_default_vs_in_alpha = 2
                Uniform block 'vs_params':
                    C struct: sprite_default_vs_params_t
                    Bind slot: SLOT_sprite_default_vs_params = 0
            Fragment shader: fs
                Uniform block 'fs_params':
                    C struct: sprite_default_fs_params_t
                    Bind slot: SLOT_sprite_default_fs_params = 0
                Image 'u_image':
                    Type: SG_IMAGETYPE_2D
                    Component Type: SG_SAMPLERTYPE_FLOAT
                    Bind slot: SLOT_sprite_default_u_image = 0


    Shader descriptor structs:

        sg_shader shd = sg_make_shader(sprite_default_shd_shader_desc());

    Vertex attribute locations for vertex shader 'vs':

        sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc){
            .layout = {
                .attrs = {
                    [ATTR_sprite_default_vs_in_pos] = { ... },
                    [ATTR_sprite_default_vs_in_uv] = { ... },
                    [ATTR_sprite_default_vs_in_alpha] = { ... },
                },
            },
            ...});

    Image bind slots, use as index in sg_bindings.vs_images[] or .fs_images[]

        SLOT_sprite_default_u_image = 0;

    Bind slot and C-struct for uniform block 'vs_params':

        sprite_default_vs_params_t vs_params = {
            .u_mvp = ...;
        };
        sg_apply_uniforms(SG_SHADERSTAGE_[VS|FS], SLOT_sprite_default_vs_params, &vs_params, sizeof(vs_params));

    Bind slot and C-struct for uniform block 'fs_params':

        sprite_default_fs_params_t fs_params = {
            .u_tint = ...;
        };
        sg_apply_uniforms(SG_SHADERSTAGE_[VS|FS], SLOT_sprite_default_fs_params, &fs_params, sizeof(fs_params));

*/
#include <stdint.h>
#include <stdbool.h>
#if !defined(SOKOL_SHDC_ALIGN)
  #if defined(_MSC_VER)
    #define SOKOL_SHDC_ALIGN(a) __declspec(align(a))
  #else
    #define SOKOL_SHDC_ALIGN(a) __attribute__((aligned(a)))
  #endif
#endif
#define ATTR_sprite_default_vs_in_pos (0)
#define ATTR_sprite_default_vs_in_uv (1)
#define ATTR_sprite_default_vs_in_alpha (2)
#define SLOT_sprite_default_u_image (0)
#define SLOT_sprite_default_vs_params (0)
#pragma pack(push,1)
SOKOL_SHDC_ALIGN(16) typedef struct sprite_default_vs_params_t {
    cute::matrix_t u_mvp;
} sprite_default_vs_params_t;
#pragma pack(pop)
#define SLOT_sprite_default_fs_params (0)
#pragma pack(push,1)
SOKOL_SHDC_ALIGN(16) typedef struct sprite_default_fs_params_t {
    cute::color_t u_tint;
} sprite_default_fs_params_t;
#pragma pack(pop)
#if defined(SOKOL_GLCORE33)
/*
    #version 330
    
    uniform vec4 vs_params[4];
    layout(location = 0) in vec2 in_pos;
    out vec2 uv;
    layout(location = 1) in vec2 in_uv;
    out float alpha;
    layout(location = 2) in float in_alpha;
    
    void main()
    {
        uv = in_uv;
        alpha = in_alpha;
        gl_Position = mat4(vs_params[0], vs_params[1], vs_params[2], vs_params[3]) * vec4(round(in_pos), 0.0, 1.0);
        gl_Position.y = -gl_Position.y;
    }
    
*/
static const char sprite_default_vs_source_glsl330[389] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x33,0x30,0x0a,0x0a,0x75,0x6e,
    0x69,0x66,0x6f,0x72,0x6d,0x20,0x76,0x65,0x63,0x34,0x20,0x76,0x73,0x5f,0x70,0x61,
    0x72,0x61,0x6d,0x73,0x5b,0x34,0x5d,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,
    0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x30,0x29,0x20,0x69,0x6e,
    0x20,0x76,0x65,0x63,0x32,0x20,0x69,0x6e,0x5f,0x70,0x6f,0x73,0x3b,0x0a,0x6f,0x75,
    0x74,0x20,0x76,0x65,0x63,0x32,0x20,0x75,0x76,0x3b,0x0a,0x6c,0x61,0x79,0x6f,0x75,
    0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x31,0x29,0x20,
    0x69,0x6e,0x20,0x76,0x65,0x63,0x32,0x20,0x69,0x6e,0x5f,0x75,0x76,0x3b,0x0a,0x6f,
    0x75,0x74,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,
    0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x20,
    0x3d,0x20,0x32,0x29,0x20,0x69,0x6e,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x69,0x6e,
    0x5f,0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,0x0a,0x76,0x6f,0x69,0x64,0x20,0x6d,0x61,
    0x69,0x6e,0x28,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x75,0x76,0x20,0x3d,0x20,
    0x69,0x6e,0x5f,0x75,0x76,0x3b,0x0a,0x20,0x20,0x20,0x20,0x61,0x6c,0x70,0x68,0x61,
    0x20,0x3d,0x20,0x69,0x6e,0x5f,0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,0x20,0x20,0x20,
    0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x6d,
    0x61,0x74,0x34,0x28,0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x30,0x5d,
    0x2c,0x20,0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x31,0x5d,0x2c,0x20,
    0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x32,0x5d,0x2c,0x20,0x76,0x73,
    0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x5b,0x33,0x5d,0x29,0x20,0x2a,0x20,0x76,0x65,
    0x63,0x34,0x28,0x72,0x6f,0x75,0x6e,0x64,0x28,0x69,0x6e,0x5f,0x70,0x6f,0x73,0x29,
    0x2c,0x20,0x30,0x2e,0x30,0x2c,0x20,0x31,0x2e,0x30,0x29,0x3b,0x0a,0x20,0x20,0x20,
    0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x2e,0x79,0x20,0x3d,
    0x20,0x2d,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x2e,0x79,0x3b,
    0x0a,0x7d,0x0a,0x0a,0x00,
};
/*
    #version 330
    
    uniform vec4 fs_params[1];
    uniform sampler2D u_image;
    
    in vec2 uv;
    in float alpha;
    layout(location = 0) out vec4 result;
    
    vec4 overlay(vec4 base, vec4 blend)
    {
        return vec4((((base.xyz * 2.0) * blend.xyz) * blend.w) + (base.xyz * (1.0 - blend.w)), base.w);
    }
    
    void main()
    {
        vec4 _59 = texture(u_image, uv);
        vec4 color = _59;
        vec4 param = _59;
        vec4 param_1 = fs_params[0];
        vec4 _71 = overlay(param, param_1);
        float _77 = _71.w * alpha;
        vec4 _92 = _71;
        _92.w = _77;
        color = _92;
        if (_77 < 9.9999997473787516355514526367188e-06)
        {
            discard;
        }
        result = color;
    }
    
*/
static const char sprite_default_fs_source_glsl330[636] = {
    0x23,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x20,0x33,0x33,0x30,0x0a,0x0a,0x75,0x6e,
    0x69,0x66,0x6f,0x72,0x6d,0x20,0x76,0x65,0x63,0x34,0x20,0x66,0x73,0x5f,0x70,0x61,
    0x72,0x61,0x6d,0x73,0x5b,0x31,0x5d,0x3b,0x0a,0x75,0x6e,0x69,0x66,0x6f,0x72,0x6d,
    0x20,0x73,0x61,0x6d,0x70,0x6c,0x65,0x72,0x32,0x44,0x20,0x75,0x5f,0x69,0x6d,0x61,
    0x67,0x65,0x3b,0x0a,0x0a,0x69,0x6e,0x20,0x76,0x65,0x63,0x32,0x20,0x75,0x76,0x3b,
    0x0a,0x69,0x6e,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x61,0x6c,0x70,0x68,0x61,0x3b,
    0x0a,0x6c,0x61,0x79,0x6f,0x75,0x74,0x28,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,
    0x20,0x3d,0x20,0x30,0x29,0x20,0x6f,0x75,0x74,0x20,0x76,0x65,0x63,0x34,0x20,0x72,
    0x65,0x73,0x75,0x6c,0x74,0x3b,0x0a,0x0a,0x76,0x65,0x63,0x34,0x20,0x6f,0x76,0x65,
    0x72,0x6c,0x61,0x79,0x28,0x76,0x65,0x63,0x34,0x20,0x62,0x61,0x73,0x65,0x2c,0x20,
    0x76,0x65,0x63,0x34,0x20,0x62,0x6c,0x65,0x6e,0x64,0x29,0x0a,0x7b,0x0a,0x20,0x20,
    0x20,0x20,0x72,0x65,0x74,0x75,0x72,0x6e,0x20,0x76,0x65,0x63,0x34,0x28,0x28,0x28,
    0x28,0x62,0x61,0x73,0x65,0x2e,0x78,0x79,0x7a,0x20,0x2a,0x20,0x32,0x2e,0x30,0x29,
    0x20,0x2a,0x20,0x62,0x6c,0x65,0x6e,0x64,0x2e,0x78,0x79,0x7a,0x29,0x20,0x2a,0x20,
    0x62,0x6c,0x65,0x6e,0x64,0x2e,0x77,0x29,0x20,0x2b,0x20,0x28,0x62,0x61,0x73,0x65,
    0x2e,0x78,0x79,0x7a,0x20,0x2a,0x20,0x28,0x31,0x2e,0x30,0x20,0x2d,0x20,0x62,0x6c,
    0x65,0x6e,0x64,0x2e,0x77,0x29,0x29,0x2c,0x20,0x62,0x61,0x73,0x65,0x2e,0x77,0x29,
    0x3b,0x0a,0x7d,0x0a,0x0a,0x76,0x6f,0x69,0x64,0x20,0x6d,0x61,0x69,0x6e,0x28,0x29,
    0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x76,0x65,0x63,0x34,0x20,0x5f,0x35,0x39,0x20,
    0x3d,0x20,0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x28,0x75,0x5f,0x69,0x6d,0x61,0x67,
    0x65,0x2c,0x20,0x75,0x76,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x76,0x65,0x63,0x34,
    0x20,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x5f,0x35,0x39,0x3b,0x0a,0x20,0x20,
    0x20,0x20,0x76,0x65,0x63,0x34,0x20,0x70,0x61,0x72,0x61,0x6d,0x20,0x3d,0x20,0x5f,
    0x35,0x39,0x3b,0x0a,0x20,0x20,0x20,0x20,0x76,0x65,0x63,0x34,0x20,0x70,0x61,0x72,
    0x61,0x6d,0x5f,0x31,0x20,0x3d,0x20,0x66,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,
    0x5b,0x30,0x5d,0x3b,0x0a,0x20,0x20,0x20,0x20,0x76,0x65,0x63,0x34,0x20,0x5f,0x37,
    0x31,0x20,0x3d,0x20,0x6f,0x76,0x65,0x72,0x6c,0x61,0x79,0x28,0x70,0x61,0x72,0x61,
    0x6d,0x2c,0x20,0x70,0x61,0x72,0x61,0x6d,0x5f,0x31,0x29,0x3b,0x0a,0x20,0x20,0x20,
    0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x5f,0x37,0x37,0x20,0x3d,0x20,0x5f,0x37,0x31,
    0x2e,0x77,0x20,0x2a,0x20,0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,0x20,0x20,0x20,0x20,
    0x76,0x65,0x63,0x34,0x20,0x5f,0x39,0x32,0x20,0x3d,0x20,0x5f,0x37,0x31,0x3b,0x0a,
    0x20,0x20,0x20,0x20,0x5f,0x39,0x32,0x2e,0x77,0x20,0x3d,0x20,0x5f,0x37,0x37,0x3b,
    0x0a,0x20,0x20,0x20,0x20,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x5f,0x39,0x32,
    0x3b,0x0a,0x20,0x20,0x20,0x20,0x69,0x66,0x20,0x28,0x5f,0x37,0x37,0x20,0x3c,0x20,
    0x39,0x2e,0x39,0x39,0x39,0x39,0x39,0x39,0x37,0x34,0x37,0x33,0x37,0x38,0x37,0x35,
    0x31,0x36,0x33,0x35,0x35,0x35,0x31,0x34,0x35,0x32,0x36,0x33,0x36,0x37,0x31,0x38,
    0x38,0x65,0x2d,0x30,0x36,0x29,0x0a,0x20,0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x64,0x69,0x73,0x63,0x61,0x72,0x64,0x3b,0x0a,0x20,0x20,
    0x20,0x20,0x7d,0x0a,0x20,0x20,0x20,0x20,0x72,0x65,0x73,0x75,0x6c,0x74,0x20,0x3d,
    0x20,0x63,0x6f,0x6c,0x6f,0x72,0x3b,0x0a,0x7d,0x0a,0x0a,0x00,
};
#endif /* SOKOL_GLCORE33 */
#if defined(SOKOL_D3D11)
/*
    cbuffer vs_params : register(b0)
    {
        row_major float4x4 _14_u_mvp : packoffset(c0);
    };
    
    
    static float4 gl_Position;
    static float2 in_pos;
    static float2 uv;
    static float2 in_uv;
    static float alpha;
    static float in_alpha;
    
    struct SPIRV_Cross_Input
    {
        float2 in_pos : TEXCOORD0;
        float2 in_uv : TEXCOORD1;
        float in_alpha : TEXCOORD2;
    };
    
    struct SPIRV_Cross_Output
    {
        float2 uv : TEXCOORD0;
        float alpha : TEXCOORD1;
        float4 gl_Position : SV_Position;
    };
    
    #line 19 ""
    void vert_main()
    {
    #line 19 ""
    #line 20 ""
        uv = in_uv;
    #line 21 ""
        alpha = in_alpha;
        gl_Position = mul(float4(round(in_pos), 0.0f, 1.0f), _14_u_mvp);
    }
    
    SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
    {
        in_pos = stage_input.in_pos;
        in_uv = stage_input.in_uv;
        in_alpha = stage_input.in_alpha;
        vert_main();
        SPIRV_Cross_Output stage_output;
        stage_output.gl_Position = gl_Position;
        stage_output.uv = uv;
        stage_output.alpha = alpha;
        return stage_output;
    }
*/
static const char sprite_default_vs_source_hlsl5[992] = {
    0x63,0x62,0x75,0x66,0x66,0x65,0x72,0x20,0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,
    0x73,0x20,0x3a,0x20,0x72,0x65,0x67,0x69,0x73,0x74,0x65,0x72,0x28,0x62,0x30,0x29,
    0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x72,0x6f,0x77,0x5f,0x6d,0x61,0x6a,0x6f,0x72,
    0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x78,0x34,0x20,0x5f,0x31,0x34,0x5f,0x75,0x5f,
    0x6d,0x76,0x70,0x20,0x3a,0x20,0x70,0x61,0x63,0x6b,0x6f,0x66,0x66,0x73,0x65,0x74,
    0x28,0x63,0x30,0x29,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,0x0a,0x73,0x74,0x61,0x74,0x69,
    0x63,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,
    0x74,0x69,0x6f,0x6e,0x3b,0x0a,0x73,0x74,0x61,0x74,0x69,0x63,0x20,0x66,0x6c,0x6f,
    0x61,0x74,0x32,0x20,0x69,0x6e,0x5f,0x70,0x6f,0x73,0x3b,0x0a,0x73,0x74,0x61,0x74,
    0x69,0x63,0x20,0x66,0x6c,0x6f,0x61,0x74,0x32,0x20,0x75,0x76,0x3b,0x0a,0x73,0x74,
    0x61,0x74,0x69,0x63,0x20,0x66,0x6c,0x6f,0x61,0x74,0x32,0x20,0x69,0x6e,0x5f,0x75,
    0x76,0x3b,0x0a,0x73,0x74,0x61,0x74,0x69,0x63,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,
    0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,0x73,0x74,0x61,0x74,0x69,0x63,0x20,0x66,0x6c,
    0x6f,0x61,0x74,0x20,0x69,0x6e,0x5f,0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,0x0a,0x73,
    0x74,0x72,0x75,0x63,0x74,0x20,0x53,0x50,0x49,0x52,0x56,0x5f,0x43,0x72,0x6f,0x73,
    0x73,0x5f,0x49,0x6e,0x70,0x75,0x74,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,
    0x6f,0x61,0x74,0x32,0x20,0x69,0x6e,0x5f,0x70,0x6f,0x73,0x20,0x3a,0x20,0x54,0x45,
    0x58,0x43,0x4f,0x4f,0x52,0x44,0x30,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,
    0x61,0x74,0x32,0x20,0x69,0x6e,0x5f,0x75,0x76,0x20,0x3a,0x20,0x54,0x45,0x58,0x43,
    0x4f,0x4f,0x52,0x44,0x31,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,
    0x20,0x69,0x6e,0x5f,0x61,0x6c,0x70,0x68,0x61,0x20,0x3a,0x20,0x54,0x45,0x58,0x43,
    0x4f,0x4f,0x52,0x44,0x32,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,
    0x74,0x20,0x53,0x50,0x49,0x52,0x56,0x5f,0x43,0x72,0x6f,0x73,0x73,0x5f,0x4f,0x75,
    0x74,0x70,0x75,0x74,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,
    0x32,0x20,0x75,0x76,0x20,0x3a,0x20,0x54,0x45,0x58,0x43,0x4f,0x4f,0x52,0x44,0x30,
    0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x61,0x6c,0x70,0x68,
    0x61,0x20,0x3a,0x20,0x54,0x45,0x58,0x43,0x4f,0x4f,0x52,0x44,0x31,0x3b,0x0a,0x20,
    0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,
    0x69,0x74,0x69,0x6f,0x6e,0x20,0x3a,0x20,0x53,0x56,0x5f,0x50,0x6f,0x73,0x69,0x74,
    0x69,0x6f,0x6e,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,
    0x39,0x20,0x22,0x22,0x0a,0x76,0x6f,0x69,0x64,0x20,0x76,0x65,0x72,0x74,0x5f,0x6d,
    0x61,0x69,0x6e,0x28,0x29,0x0a,0x7b,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,0x39,
    0x20,0x22,0x22,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x32,0x30,0x20,0x22,0x22,0x0a,
    0x20,0x20,0x20,0x20,0x75,0x76,0x20,0x3d,0x20,0x69,0x6e,0x5f,0x75,0x76,0x3b,0x0a,
    0x23,0x6c,0x69,0x6e,0x65,0x20,0x32,0x31,0x20,0x22,0x22,0x0a,0x20,0x20,0x20,0x20,
    0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x69,0x6e,0x5f,0x61,0x6c,0x70,0x68,0x61,
    0x3b,0x0a,0x20,0x20,0x20,0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,
    0x6e,0x20,0x3d,0x20,0x6d,0x75,0x6c,0x28,0x66,0x6c,0x6f,0x61,0x74,0x34,0x28,0x72,
    0x6f,0x75,0x6e,0x64,0x28,0x69,0x6e,0x5f,0x70,0x6f,0x73,0x29,0x2c,0x20,0x30,0x2e,
    0x30,0x66,0x2c,0x20,0x31,0x2e,0x30,0x66,0x29,0x2c,0x20,0x5f,0x31,0x34,0x5f,0x75,
    0x5f,0x6d,0x76,0x70,0x29,0x3b,0x0a,0x7d,0x0a,0x0a,0x53,0x50,0x49,0x52,0x56,0x5f,
    0x43,0x72,0x6f,0x73,0x73,0x5f,0x4f,0x75,0x74,0x70,0x75,0x74,0x20,0x6d,0x61,0x69,
    0x6e,0x28,0x53,0x50,0x49,0x52,0x56,0x5f,0x43,0x72,0x6f,0x73,0x73,0x5f,0x49,0x6e,
    0x70,0x75,0x74,0x20,0x73,0x74,0x61,0x67,0x65,0x5f,0x69,0x6e,0x70,0x75,0x74,0x29,
    0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x69,0x6e,0x5f,0x70,0x6f,0x73,0x20,0x3d,0x20,
    0x73,0x74,0x61,0x67,0x65,0x5f,0x69,0x6e,0x70,0x75,0x74,0x2e,0x69,0x6e,0x5f,0x70,
    0x6f,0x73,0x3b,0x0a,0x20,0x20,0x20,0x20,0x69,0x6e,0x5f,0x75,0x76,0x20,0x3d,0x20,
    0x73,0x74,0x61,0x67,0x65,0x5f,0x69,0x6e,0x70,0x75,0x74,0x2e,0x69,0x6e,0x5f,0x75,
    0x76,0x3b,0x0a,0x20,0x20,0x20,0x20,0x69,0x6e,0x5f,0x61,0x6c,0x70,0x68,0x61,0x20,
    0x3d,0x20,0x73,0x74,0x61,0x67,0x65,0x5f,0x69,0x6e,0x70,0x75,0x74,0x2e,0x69,0x6e,
    0x5f,0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,0x20,0x20,0x20,0x20,0x76,0x65,0x72,0x74,
    0x5f,0x6d,0x61,0x69,0x6e,0x28,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x53,0x50,0x49,
    0x52,0x56,0x5f,0x43,0x72,0x6f,0x73,0x73,0x5f,0x4f,0x75,0x74,0x70,0x75,0x74,0x20,
    0x73,0x74,0x61,0x67,0x65,0x5f,0x6f,0x75,0x74,0x70,0x75,0x74,0x3b,0x0a,0x20,0x20,
    0x20,0x20,0x73,0x74,0x61,0x67,0x65,0x5f,0x6f,0x75,0x74,0x70,0x75,0x74,0x2e,0x67,
    0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x67,0x6c,0x5f,
    0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x3b,0x0a,0x20,0x20,0x20,0x20,0x73,0x74,
    0x61,0x67,0x65,0x5f,0x6f,0x75,0x74,0x70,0x75,0x74,0x2e,0x75,0x76,0x20,0x3d,0x20,
    0x75,0x76,0x3b,0x0a,0x20,0x20,0x20,0x20,0x73,0x74,0x61,0x67,0x65,0x5f,0x6f,0x75,
    0x74,0x70,0x75,0x74,0x2e,0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x61,0x6c,0x70,
    0x68,0x61,0x3b,0x0a,0x20,0x20,0x20,0x20,0x72,0x65,0x74,0x75,0x72,0x6e,0x20,0x73,
    0x74,0x61,0x67,0x65,0x5f,0x6f,0x75,0x74,0x70,0x75,0x74,0x3b,0x0a,0x7d,0x0a,0x00,

};
/*
    cbuffer fs_params : register(b0)
    {
        float4 _62_u_tint : packoffset(c0);
    };
    
    Texture2D<float4> u_image : register(t0);
    SamplerState _u_image_sampler : register(s0);
    
    static float2 uv;
    static float alpha;
    static float4 result;
    
    struct SPIRV_Cross_Input
    {
        float2 uv : TEXCOORD0;
        float alpha : TEXCOORD1;
    };
    
    struct SPIRV_Cross_Output
    {
        float4 result : SV_Target0;
    };
    
    #line 19 ""
    float4 overlay(float4 base, float4 blend)
    {
    #line 19 ""
    #line 20 ""
        return float4((((base.xyz * 2.0f) * blend.xyz) * blend.w) + (base.xyz * (1.0f - blend.w)), base.w);
    }
    
    #line 26 ""
    void frag_main()
    {
    #line 26 ""
        float4 _59 = u_image.Sample(_u_image_sampler, uv);
        float4 color = _59;
        float4 param = _59;
        float4 param_1 = _62_u_tint;
        float4 _71 = overlay(param, param_1);
        float _77 = _71.w * alpha;
        float4 _92 = _71;
        _92.w = _77;
        color = _92;
        if (_77 < 9.9999997473787516355514526367188e-06f)
        {
            discard;
        }
    #line 30 ""
        result = color;
    }
    
    SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
    {
        uv = stage_input.uv;
        alpha = stage_input.alpha;
        frag_main();
        SPIRV_Cross_Output stage_output;
        stage_output.result = result;
        return stage_output;
    }
*/
static const char sprite_default_fs_source_hlsl5[1222] = {
    0x63,0x62,0x75,0x66,0x66,0x65,0x72,0x20,0x66,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,
    0x73,0x20,0x3a,0x20,0x72,0x65,0x67,0x69,0x73,0x74,0x65,0x72,0x28,0x62,0x30,0x29,
    0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x5f,0x36,
    0x32,0x5f,0x75,0x5f,0x74,0x69,0x6e,0x74,0x20,0x3a,0x20,0x70,0x61,0x63,0x6b,0x6f,
    0x66,0x66,0x73,0x65,0x74,0x28,0x63,0x30,0x29,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,0x54,
    0x65,0x78,0x74,0x75,0x72,0x65,0x32,0x44,0x3c,0x66,0x6c,0x6f,0x61,0x74,0x34,0x3e,
    0x20,0x75,0x5f,0x69,0x6d,0x61,0x67,0x65,0x20,0x3a,0x20,0x72,0x65,0x67,0x69,0x73,
    0x74,0x65,0x72,0x28,0x74,0x30,0x29,0x3b,0x0a,0x53,0x61,0x6d,0x70,0x6c,0x65,0x72,
    0x53,0x74,0x61,0x74,0x65,0x20,0x5f,0x75,0x5f,0x69,0x6d,0x61,0x67,0x65,0x5f,0x73,
    0x61,0x6d,0x70,0x6c,0x65,0x72,0x20,0x3a,0x20,0x72,0x65,0x67,0x69,0x73,0x74,0x65,
    0x72,0x28,0x73,0x30,0x29,0x3b,0x0a,0x0a,0x73,0x74,0x61,0x74,0x69,0x63,0x20,0x66,
    0x6c,0x6f,0x61,0x74,0x32,0x20,0x75,0x76,0x3b,0x0a,0x73,0x74,0x61,0x74,0x69,0x63,
    0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,0x73,0x74,
    0x61,0x74,0x69,0x63,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x72,0x65,0x73,0x75,
    0x6c,0x74,0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x53,0x50,0x49,0x52,
    0x56,0x5f,0x43,0x72,0x6f,0x73,0x73,0x5f,0x49,0x6e,0x70,0x75,0x74,0x0a,0x7b,0x0a,
    0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x32,0x20,0x75,0x76,0x20,0x3a,0x20,
    0x54,0x45,0x58,0x43,0x4f,0x4f,0x52,0x44,0x30,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,
    0x6c,0x6f,0x61,0x74,0x20,0x61,0x6c,0x70,0x68,0x61,0x20,0x3a,0x20,0x54,0x45,0x58,
    0x43,0x4f,0x4f,0x52,0x44,0x31,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,
    0x63,0x74,0x20,0x53,0x50,0x49,0x52,0x56,0x5f,0x43,0x72,0x6f,0x73,0x73,0x5f,0x4f,
    0x75,0x74,0x70,0x75,0x74,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,
    0x74,0x34,0x20,0x72,0x65,0x73,0x75,0x6c,0x74,0x20,0x3a,0x20,0x53,0x56,0x5f,0x54,
    0x61,0x72,0x67,0x65,0x74,0x30,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,0x23,0x6c,0x69,0x6e,
    0x65,0x20,0x31,0x39,0x20,0x22,0x22,0x0a,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x6f,
    0x76,0x65,0x72,0x6c,0x61,0x79,0x28,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x62,0x61,
    0x73,0x65,0x2c,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x62,0x6c,0x65,0x6e,0x64,
    0x29,0x0a,0x7b,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,0x39,0x20,0x22,0x22,0x0a,
    0x23,0x6c,0x69,0x6e,0x65,0x20,0x32,0x30,0x20,0x22,0x22,0x0a,0x20,0x20,0x20,0x20,
    0x72,0x65,0x74,0x75,0x72,0x6e,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x28,0x28,0x28,
    0x28,0x62,0x61,0x73,0x65,0x2e,0x78,0x79,0x7a,0x20,0x2a,0x20,0x32,0x2e,0x30,0x66,
    0x29,0x20,0x2a,0x20,0x62,0x6c,0x65,0x6e,0x64,0x2e,0x78,0x79,0x7a,0x29,0x20,0x2a,
    0x20,0x62,0x6c,0x65,0x6e,0x64,0x2e,0x77,0x29,0x20,0x2b,0x20,0x28,0x62,0x61,0x73,
    0x65,0x2e,0x78,0x79,0x7a,0x20,0x2a,0x20,0x28,0x31,0x2e,0x30,0x66,0x20,0x2d,0x20,
    0x62,0x6c,0x65,0x6e,0x64,0x2e,0x77,0x29,0x29,0x2c,0x20,0x62,0x61,0x73,0x65,0x2e,
    0x77,0x29,0x3b,0x0a,0x7d,0x0a,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x32,0x36,0x20,
    0x22,0x22,0x0a,0x76,0x6f,0x69,0x64,0x20,0x66,0x72,0x61,0x67,0x5f,0x6d,0x61,0x69,
    0x6e,0x28,0x29,0x0a,0x7b,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x32,0x36,0x20,0x22,
    0x22,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x5f,0x35,0x39,
    0x20,0x3d,0x20,0x75,0x5f,0x69,0x6d,0x61,0x67,0x65,0x2e,0x53,0x61,0x6d,0x70,0x6c,
    0x65,0x28,0x5f,0x75,0x5f,0x69,0x6d,0x61,0x67,0x65,0x5f,0x73,0x61,0x6d,0x70,0x6c,
    0x65,0x72,0x2c,0x20,0x75,0x76,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,
    0x61,0x74,0x34,0x20,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x5f,0x35,0x39,0x3b,
    0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x70,0x61,0x72,0x61,
    0x6d,0x20,0x3d,0x20,0x5f,0x35,0x39,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,
    0x61,0x74,0x34,0x20,0x70,0x61,0x72,0x61,0x6d,0x5f,0x31,0x20,0x3d,0x20,0x5f,0x36,
    0x32,0x5f,0x75,0x5f,0x74,0x69,0x6e,0x74,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,
    0x6f,0x61,0x74,0x34,0x20,0x5f,0x37,0x31,0x20,0x3d,0x20,0x6f,0x76,0x65,0x72,0x6c,
    0x61,0x79,0x28,0x70,0x61,0x72,0x61,0x6d,0x2c,0x20,0x70,0x61,0x72,0x61,0x6d,0x5f,
    0x31,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x5f,0x37,
    0x37,0x20,0x3d,0x20,0x5f,0x37,0x31,0x2e,0x77,0x20,0x2a,0x20,0x61,0x6c,0x70,0x68,
    0x61,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x5f,0x39,
    0x32,0x20,0x3d,0x20,0x5f,0x37,0x31,0x3b,0x0a,0x20,0x20,0x20,0x20,0x5f,0x39,0x32,
    0x2e,0x77,0x20,0x3d,0x20,0x5f,0x37,0x37,0x3b,0x0a,0x20,0x20,0x20,0x20,0x63,0x6f,
    0x6c,0x6f,0x72,0x20,0x3d,0x20,0x5f,0x39,0x32,0x3b,0x0a,0x20,0x20,0x20,0x20,0x69,
    0x66,0x20,0x28,0x5f,0x37,0x37,0x20,0x3c,0x20,0x39,0x2e,0x39,0x39,0x39,0x39,0x39,
    0x39,0x37,0x34,0x37,0x33,0x37,0x38,0x37,0x35,0x31,0x36,0x33,0x35,0x35,0x35,0x31,
    0x34,0x35,0x32,0x36,0x33,0x36,0x37,0x31,0x38,0x38,0x65,0x2d,0x30,0x36,0x66,0x29,
    0x0a,0x20,0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x64,
    0x69,0x73,0x63,0x61,0x72,0x64,0x3b,0x0a,0x20,0x20,0x20,0x20,0x7d,0x0a,0x23,0x6c,
    0x69,0x6e,0x65,0x20,0x33,0x30,0x20,0x22,0x22,0x0a,0x20,0x20,0x20,0x20,0x72,0x65,
    0x73,0x75,0x6c,0x74,0x20,0x3d,0x20,0x63,0x6f,0x6c,0x6f,0x72,0x3b,0x0a,0x7d,0x0a,
    0x0a,0x53,0x50,0x49,0x52,0x56,0x5f,0x43,0x72,0x6f,0x73,0x73,0x5f,0x4f,0x75,0x74,
    0x70,0x75,0x74,0x20,0x6d,0x61,0x69,0x6e,0x28,0x53,0x50,0x49,0x52,0x56,0x5f,0x43,
    0x72,0x6f,0x73,0x73,0x5f,0x49,0x6e,0x70,0x75,0x74,0x20,0x73,0x74,0x61,0x67,0x65,
    0x5f,0x69,0x6e,0x70,0x75,0x74,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x75,0x76,
    0x20,0x3d,0x20,0x73,0x74,0x61,0x67,0x65,0x5f,0x69,0x6e,0x70,0x75,0x74,0x2e,0x75,
    0x76,0x3b,0x0a,0x20,0x20,0x20,0x20,0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x73,
    0x74,0x61,0x67,0x65,0x5f,0x69,0x6e,0x70,0x75,0x74,0x2e,0x61,0x6c,0x70,0x68,0x61,
    0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x72,0x61,0x67,0x5f,0x6d,0x61,0x69,0x6e,0x28,
    0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x53,0x50,0x49,0x52,0x56,0x5f,0x43,0x72,0x6f,
    0x73,0x73,0x5f,0x4f,0x75,0x74,0x70,0x75,0x74,0x20,0x73,0x74,0x61,0x67,0x65,0x5f,
    0x6f,0x75,0x74,0x70,0x75,0x74,0x3b,0x0a,0x20,0x20,0x20,0x20,0x73,0x74,0x61,0x67,
    0x65,0x5f,0x6f,0x75,0x74,0x70,0x75,0x74,0x2e,0x72,0x65,0x73,0x75,0x6c,0x74,0x20,
    0x3d,0x20,0x72,0x65,0x73,0x75,0x6c,0x74,0x3b,0x0a,0x20,0x20,0x20,0x20,0x72,0x65,
    0x74,0x75,0x72,0x6e,0x20,0x73,0x74,0x61,0x67,0x65,0x5f,0x6f,0x75,0x74,0x70,0x75,
    0x74,0x3b,0x0a,0x7d,0x0a,0x00,
};
#endif /* SOKOL_D3D11 */
#if defined(SOKOL_METAL)
/*
    #include <metal_stdlib>
    #include <simd/simd.h>
    
    using namespace metal;
    
    struct vs_params
    {
        float4x4 u_mvp;
    };
    
    struct main0_out
    {
        float2 uv [[user(locn0)]];
        float alpha [[user(locn1)]];
        float4 gl_Position [[position]];
    };
    
    struct main0_in
    {
        float2 in_pos [[attribute(0)]];
        float2 in_uv [[attribute(1)]];
        float in_alpha [[attribute(2)]];
    };
    
    #line 19 ""
    vertex main0_out main0(main0_in in [[stage_in]], constant vs_params& _14 [[buffer(0)]])
    {
        main0_out out = {};
    #line 19 ""
    #line 20 ""
        out.uv = in.in_uv;
    #line 21 ""
        out.alpha = in.in_alpha;
        out.gl_Position = _14.u_mvp * float4(round(in.in_pos), 0.0, 1.0);
        return out;
    }
    
*/
static const char sprite_default_vs_source_metal_macos[673] = {
    0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,0x20,0x3c,0x6d,0x65,0x74,0x61,0x6c,0x5f,
    0x73,0x74,0x64,0x6c,0x69,0x62,0x3e,0x0a,0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,
    0x20,0x3c,0x73,0x69,0x6d,0x64,0x2f,0x73,0x69,0x6d,0x64,0x2e,0x68,0x3e,0x0a,0x0a,
    0x75,0x73,0x69,0x6e,0x67,0x20,0x6e,0x61,0x6d,0x65,0x73,0x70,0x61,0x63,0x65,0x20,
    0x6d,0x65,0x74,0x61,0x6c,0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x76,
    0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,
    0x6c,0x6f,0x61,0x74,0x34,0x78,0x34,0x20,0x75,0x5f,0x6d,0x76,0x70,0x3b,0x0a,0x7d,
    0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,
    0x6f,0x75,0x74,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x32,
    0x20,0x75,0x76,0x20,0x5b,0x5b,0x75,0x73,0x65,0x72,0x28,0x6c,0x6f,0x63,0x6e,0x30,
    0x29,0x5d,0x5d,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x61,
    0x6c,0x70,0x68,0x61,0x20,0x5b,0x5b,0x75,0x73,0x65,0x72,0x28,0x6c,0x6f,0x63,0x6e,
    0x31,0x29,0x5d,0x5d,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,
    0x20,0x67,0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x20,0x5b,0x5b,0x70,
    0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x5d,0x5d,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,0x73,
    0x74,0x72,0x75,0x63,0x74,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x69,0x6e,0x0a,0x7b,
    0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x32,0x20,0x69,0x6e,0x5f,0x70,
    0x6f,0x73,0x20,0x5b,0x5b,0x61,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x28,0x30,
    0x29,0x5d,0x5d,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x32,0x20,
    0x69,0x6e,0x5f,0x75,0x76,0x20,0x5b,0x5b,0x61,0x74,0x74,0x72,0x69,0x62,0x75,0x74,
    0x65,0x28,0x31,0x29,0x5d,0x5d,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,
    0x74,0x20,0x69,0x6e,0x5f,0x61,0x6c,0x70,0x68,0x61,0x20,0x5b,0x5b,0x61,0x74,0x74,
    0x72,0x69,0x62,0x75,0x74,0x65,0x28,0x32,0x29,0x5d,0x5d,0x3b,0x0a,0x7d,0x3b,0x0a,
    0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,0x39,0x20,0x22,0x22,0x0a,0x76,0x65,0x72,
    0x74,0x65,0x78,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x6f,0x75,0x74,0x20,0x6d,0x61,
    0x69,0x6e,0x30,0x28,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x69,0x6e,0x20,0x69,0x6e,0x20,
    0x5b,0x5b,0x73,0x74,0x61,0x67,0x65,0x5f,0x69,0x6e,0x5d,0x5d,0x2c,0x20,0x63,0x6f,
    0x6e,0x73,0x74,0x61,0x6e,0x74,0x20,0x76,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,
    0x26,0x20,0x5f,0x31,0x34,0x20,0x5b,0x5b,0x62,0x75,0x66,0x66,0x65,0x72,0x28,0x30,
    0x29,0x5d,0x5d,0x29,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x6d,0x61,0x69,0x6e,0x30,
    0x5f,0x6f,0x75,0x74,0x20,0x6f,0x75,0x74,0x20,0x3d,0x20,0x7b,0x7d,0x3b,0x0a,0x23,
    0x6c,0x69,0x6e,0x65,0x20,0x31,0x39,0x20,0x22,0x22,0x0a,0x23,0x6c,0x69,0x6e,0x65,
    0x20,0x32,0x30,0x20,0x22,0x22,0x0a,0x20,0x20,0x20,0x20,0x6f,0x75,0x74,0x2e,0x75,
    0x76,0x20,0x3d,0x20,0x69,0x6e,0x2e,0x69,0x6e,0x5f,0x75,0x76,0x3b,0x0a,0x23,0x6c,
    0x69,0x6e,0x65,0x20,0x32,0x31,0x20,0x22,0x22,0x0a,0x20,0x20,0x20,0x20,0x6f,0x75,
    0x74,0x2e,0x61,0x6c,0x70,0x68,0x61,0x20,0x3d,0x20,0x69,0x6e,0x2e,0x69,0x6e,0x5f,
    0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,0x20,0x20,0x20,0x20,0x6f,0x75,0x74,0x2e,0x67,
    0x6c,0x5f,0x50,0x6f,0x73,0x69,0x74,0x69,0x6f,0x6e,0x20,0x3d,0x20,0x5f,0x31,0x34,
    0x2e,0x75,0x5f,0x6d,0x76,0x70,0x20,0x2a,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x28,
    0x72,0x6f,0x75,0x6e,0x64,0x28,0x69,0x6e,0x2e,0x69,0x6e,0x5f,0x70,0x6f,0x73,0x29,
    0x2c,0x20,0x30,0x2e,0x30,0x2c,0x20,0x31,0x2e,0x30,0x29,0x3b,0x0a,0x20,0x20,0x20,
    0x20,0x72,0x65,0x74,0x75,0x72,0x6e,0x20,0x6f,0x75,0x74,0x3b,0x0a,0x7d,0x0a,0x0a,
    0x00,
};
/*
    #pragma clang diagnostic ignored "-Wmissing-prototypes"
    
    #include <metal_stdlib>
    #include <simd/simd.h>
    
    using namespace metal;
    
    struct fs_params
    {
        float4 u_tint;
    };
    
    struct main0_out
    {
        float4 result [[color(0)]];
    };
    
    struct main0_in
    {
        float2 uv [[user(locn0)]];
        float alpha [[user(locn1)]];
    };
    
    #line 19 ""
    static inline __attribute__((always_inline))
    float4 overlay(thread const float4& base, thread const float4& blend)
    {
    #line 19 ""
    #line 20 ""
        return float4((((base.xyz * 2.0) * blend.xyz) * blend.w) + (base.xyz * (1.0 - blend.w)), base.w);
    }
    
    #line 26 ""
    fragment main0_out main0(main0_in in [[stage_in]], constant fs_params& _62 [[buffer(0)]], texture2d<float> u_image [[texture(0)]], sampler u_imageSmplr [[sampler(0)]])
    {
        main0_out out = {};
    #line 26 ""
        float4 _59 = u_image.sample(u_imageSmplr, in.uv);
        float4 color = _59;
        float4 param = _59;
        float4 param_1 = _62.u_tint;
        float4 _71 = overlay(param, param_1);
        float _77 = _71.w * in.alpha;
        float4 _92 = _71;
        _92.w = _77;
        color = _92;
        if (_77 < 9.9999997473787516355514526367188e-06)
        {
            discard_fragment();
        }
    #line 30 ""
        out.result = color;
        return out;
    }
    
*/
static const char sprite_default_fs_source_metal_macos[1204] = {
    0x23,0x70,0x72,0x61,0x67,0x6d,0x61,0x20,0x63,0x6c,0x61,0x6e,0x67,0x20,0x64,0x69,
    0x61,0x67,0x6e,0x6f,0x73,0x74,0x69,0x63,0x20,0x69,0x67,0x6e,0x6f,0x72,0x65,0x64,
    0x20,0x22,0x2d,0x57,0x6d,0x69,0x73,0x73,0x69,0x6e,0x67,0x2d,0x70,0x72,0x6f,0x74,
    0x6f,0x74,0x79,0x70,0x65,0x73,0x22,0x0a,0x0a,0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,
    0x65,0x20,0x3c,0x6d,0x65,0x74,0x61,0x6c,0x5f,0x73,0x74,0x64,0x6c,0x69,0x62,0x3e,
    0x0a,0x23,0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,0x20,0x3c,0x73,0x69,0x6d,0x64,0x2f,
    0x73,0x69,0x6d,0x64,0x2e,0x68,0x3e,0x0a,0x0a,0x75,0x73,0x69,0x6e,0x67,0x20,0x6e,
    0x61,0x6d,0x65,0x73,0x70,0x61,0x63,0x65,0x20,0x6d,0x65,0x74,0x61,0x6c,0x3b,0x0a,
    0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x66,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,
    0x73,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x75,
    0x5f,0x74,0x69,0x6e,0x74,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,
    0x74,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x6f,0x75,0x74,0x0a,0x7b,0x0a,0x20,0x20,
    0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x72,0x65,0x73,0x75,0x6c,0x74,0x20,
    0x5b,0x5b,0x63,0x6f,0x6c,0x6f,0x72,0x28,0x30,0x29,0x5d,0x5d,0x3b,0x0a,0x7d,0x3b,
    0x0a,0x0a,0x73,0x74,0x72,0x75,0x63,0x74,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x69,
    0x6e,0x0a,0x7b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x32,0x20,0x75,
    0x76,0x20,0x5b,0x5b,0x75,0x73,0x65,0x72,0x28,0x6c,0x6f,0x63,0x6e,0x30,0x29,0x5d,
    0x5d,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x61,0x6c,0x70,
    0x68,0x61,0x20,0x5b,0x5b,0x75,0x73,0x65,0x72,0x28,0x6c,0x6f,0x63,0x6e,0x31,0x29,
    0x5d,0x5d,0x3b,0x0a,0x7d,0x3b,0x0a,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,0x39,
    0x20,0x22,0x22,0x0a,0x73,0x74,0x61,0x74,0x69,0x63,0x20,0x69,0x6e,0x6c,0x69,0x6e,
    0x65,0x20,0x5f,0x5f,0x61,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x5f,0x5f,0x28,
    0x28,0x61,0x6c,0x77,0x61,0x79,0x73,0x5f,0x69,0x6e,0x6c,0x69,0x6e,0x65,0x29,0x29,
    0x0a,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x6f,0x76,0x65,0x72,0x6c,0x61,0x79,0x28,
    0x74,0x68,0x72,0x65,0x61,0x64,0x20,0x63,0x6f,0x6e,0x73,0x74,0x20,0x66,0x6c,0x6f,
    0x61,0x74,0x34,0x26,0x20,0x62,0x61,0x73,0x65,0x2c,0x20,0x74,0x68,0x72,0x65,0x61,
    0x64,0x20,0x63,0x6f,0x6e,0x73,0x74,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x26,0x20,
    0x62,0x6c,0x65,0x6e,0x64,0x29,0x0a,0x7b,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x31,
    0x39,0x20,0x22,0x22,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x32,0x30,0x20,0x22,0x22,
    0x0a,0x20,0x20,0x20,0x20,0x72,0x65,0x74,0x75,0x72,0x6e,0x20,0x66,0x6c,0x6f,0x61,
    0x74,0x34,0x28,0x28,0x28,0x28,0x62,0x61,0x73,0x65,0x2e,0x78,0x79,0x7a,0x20,0x2a,
    0x20,0x32,0x2e,0x30,0x29,0x20,0x2a,0x20,0x62,0x6c,0x65,0x6e,0x64,0x2e,0x78,0x79,
    0x7a,0x29,0x20,0x2a,0x20,0x62,0x6c,0x65,0x6e,0x64,0x2e,0x77,0x29,0x20,0x2b,0x20,
    0x28,0x62,0x61,0x73,0x65,0x2e,0x78,0x79,0x7a,0x20,0x2a,0x20,0x28,0x31,0x2e,0x30,
    0x20,0x2d,0x20,0x62,0x6c,0x65,0x6e,0x64,0x2e,0x77,0x29,0x29,0x2c,0x20,0x62,0x61,
    0x73,0x65,0x2e,0x77,0x29,0x3b,0x0a,0x7d,0x0a,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,
    0x32,0x36,0x20,0x22,0x22,0x0a,0x66,0x72,0x61,0x67,0x6d,0x65,0x6e,0x74,0x20,0x6d,
    0x61,0x69,0x6e,0x30,0x5f,0x6f,0x75,0x74,0x20,0x6d,0x61,0x69,0x6e,0x30,0x28,0x6d,
    0x61,0x69,0x6e,0x30,0x5f,0x69,0x6e,0x20,0x69,0x6e,0x20,0x5b,0x5b,0x73,0x74,0x61,
    0x67,0x65,0x5f,0x69,0x6e,0x5d,0x5d,0x2c,0x20,0x63,0x6f,0x6e,0x73,0x74,0x61,0x6e,
    0x74,0x20,0x66,0x73,0x5f,0x70,0x61,0x72,0x61,0x6d,0x73,0x26,0x20,0x5f,0x36,0x32,
    0x20,0x5b,0x5b,0x62,0x75,0x66,0x66,0x65,0x72,0x28,0x30,0x29,0x5d,0x5d,0x2c,0x20,
    0x74,0x65,0x78,0x74,0x75,0x72,0x65,0x32,0x64,0x3c,0x66,0x6c,0x6f,0x61,0x74,0x3e,
    0x20,0x75,0x5f,0x69,0x6d,0x61,0x67,0x65,0x20,0x5b,0x5b,0x74,0x65,0x78,0x74,0x75,
    0x72,0x65,0x28,0x30,0x29,0x5d,0x5d,0x2c,0x20,0x73,0x61,0x6d,0x70,0x6c,0x65,0x72,
    0x20,0x75,0x5f,0x69,0x6d,0x61,0x67,0x65,0x53,0x6d,0x70,0x6c,0x72,0x20,0x5b,0x5b,
    0x73,0x61,0x6d,0x70,0x6c,0x65,0x72,0x28,0x30,0x29,0x5d,0x5d,0x29,0x0a,0x7b,0x0a,
    0x20,0x20,0x20,0x20,0x6d,0x61,0x69,0x6e,0x30,0x5f,0x6f,0x75,0x74,0x20,0x6f,0x75,
    0x74,0x20,0x3d,0x20,0x7b,0x7d,0x3b,0x0a,0x23,0x6c,0x69,0x6e,0x65,0x20,0x32,0x36,
    0x20,0x22,0x22,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x5f,
    0x35,0x39,0x20,0x3d,0x20,0x75,0x5f,0x69,0x6d,0x61,0x67,0x65,0x2e,0x73,0x61,0x6d,
    0x70,0x6c,0x65,0x28,0x75,0x5f,0x69,0x6d,0x61,0x67,0x65,0x53,0x6d,0x70,0x6c,0x72,
    0x2c,0x20,0x69,0x6e,0x2e,0x75,0x76,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,
    0x6f,0x61,0x74,0x34,0x20,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x5f,0x35,0x39,
    0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x34,0x20,0x70,0x61,0x72,
    0x61,0x6d,0x20,0x3d,0x20,0x5f,0x35,0x39,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,
    0x6f,0x61,0x74,0x34,0x20,0x70,0x61,0x72,0x61,0x6d,0x5f,0x31,0x20,0x3d,0x20,0x5f,
    0x36,0x32,0x2e,0x75,0x5f,0x74,0x69,0x6e,0x74,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,
    0x6c,0x6f,0x61,0x74,0x34,0x20,0x5f,0x37,0x31,0x20,0x3d,0x20,0x6f,0x76,0x65,0x72,
    0x6c,0x61,0x79,0x28,0x70,0x61,0x72,0x61,0x6d,0x2c,0x20,0x70,0x61,0x72,0x61,0x6d,
    0x5f,0x31,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,0x20,0x5f,
    0x37,0x37,0x20,0x3d,0x20,0x5f,0x37,0x31,0x2e,0x77,0x20,0x2a,0x20,0x69,0x6e,0x2e,
    0x61,0x6c,0x70,0x68,0x61,0x3b,0x0a,0x20,0x20,0x20,0x20,0x66,0x6c,0x6f,0x61,0x74,
    0x34,0x20,0x5f,0x39,0x32,0x20,0x3d,0x20,0x5f,0x37,0x31,0x3b,0x0a,0x20,0x20,0x20,
    0x20,0x5f,0x39,0x32,0x2e,0x77,0x20,0x3d,0x20,0x5f,0x37,0x37,0x3b,0x0a,0x20,0x20,
    0x20,0x20,0x63,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x5f,0x39,0x32,0x3b,0x0a,0x20,
    0x20,0x20,0x20,0x69,0x66,0x20,0x28,0x5f,0x37,0x37,0x20,0x3c,0x20,0x39,0x2e,0x39,
    0x39,0x39,0x39,0x39,0x39,0x37,0x34,0x37,0x33,0x37,0x38,0x37,0x35,0x31,0x36,0x33,
    0x35,0x35,0x35,0x31,0x34,0x35,0x32,0x36,0x33,0x36,0x37,0x31,0x38,0x38,0x65,0x2d,
    0x30,0x36,0x29,0x0a,0x20,0x20,0x20,0x20,0x7b,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x64,0x69,0x73,0x63,0x61,0x72,0x64,0x5f,0x66,0x72,0x61,0x67,0x6d,0x65,
    0x6e,0x74,0x28,0x29,0x3b,0x0a,0x20,0x20,0x20,0x20,0x7d,0x0a,0x23,0x6c,0x69,0x6e,
    0x65,0x20,0x33,0x30,0x20,0x22,0x22,0x0a,0x20,0x20,0x20,0x20,0x6f,0x75,0x74,0x2e,
    0x72,0x65,0x73,0x75,0x6c,0x74,0x20,0x3d,0x20,0x63,0x6f,0x6c,0x6f,0x72,0x3b,0x0a,
    0x20,0x20,0x20,0x20,0x72,0x65,0x74,0x75,0x72,0x6e,0x20,0x6f,0x75,0x74,0x3b,0x0a,
    0x7d,0x0a,0x0a,0x00,
};
#endif /* SOKOL_METAL */
#if !defined(SOKOL_GFX_INCLUDED)
  #error "Please include sokol_gfx.h before sprite_shader.h"
#endif
static inline const sg_shader_desc* sprite_default_shd_shader_desc(void) {
  #if defined(SOKOL_GLCORE33)
  if (sg_query_backend() == SG_BACKEND_GLCORE33) {
    static sg_shader_desc desc;
    static bool valid;
    if (!valid) {
      valid = true;
      desc.attrs[0].name = "in_pos";
      desc.attrs[1].name = "in_uv";
      desc.attrs[2].name = "in_alpha";
      desc.vs.source = sprite_default_vs_source_glsl330;
      desc.vs.entry = "main";
      desc.vs.uniform_blocks[0].size = 64;
      desc.vs.uniform_blocks[0].uniforms[0].name = "vs_params";
      desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
      desc.vs.uniform_blocks[0].uniforms[0].array_count = 4;
      desc.fs.source = sprite_default_fs_source_glsl330;
      desc.fs.entry = "main";
      desc.fs.uniform_blocks[0].size = 16;
      desc.fs.uniform_blocks[0].uniforms[0].name = "fs_params";
      desc.fs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_FLOAT4;
      desc.fs.uniform_blocks[0].uniforms[0].array_count = 1;
      desc.fs.images[0].name = "u_image";
      desc.fs.images[0].type = SG_IMAGETYPE_2D;
      desc.fs.images[0].sampler_type = SG_SAMPLERTYPE_FLOAT;
      desc.label = "sprite_default_shd_shader";
    };
    return &desc;
  }
  #endif /* SOKOL_GLCORE33 */
  #if defined(SOKOL_D3D11)
  if (sg_query_backend() == SG_BACKEND_D3D11) {
    static sg_shader_desc desc;
    static bool valid;
    if (!valid) {
      valid = true;
      desc.attrs[0].sem_name = "TEXCOORD";
      desc.attrs[0].sem_index = 0;
      desc.attrs[1].sem_name = "TEXCOORD";
      desc.attrs[1].sem_index = 1;
      desc.attrs[2].sem_name = "TEXCOORD";
      desc.attrs[2].sem_index = 2;
      desc.vs.source = sprite_default_vs_source_hlsl5;
      desc.vs.d3d11_target = "vs_5_0";
      desc.vs.entry = "main";
      desc.vs.uniform_blocks[0].size = 64;
      desc.fs.source = sprite_default_fs_source_hlsl5;
      desc.fs.d3d11_target = "ps_5_0";
      desc.fs.entry = "main";
      desc.fs.uniform_blocks[0].size = 16;
      desc.fs.images[0].name = "u_image";
      desc.fs.images[0].type = SG_IMAGETYPE_2D;
      desc.fs.images[0].sampler_type = SG_SAMPLERTYPE_FLOAT;
      desc.label = "sprite_default_shd_shader";
    };
    return &desc;
  }
  #endif /* SOKOL_D3D11 */
  #if defined(SOKOL_METAL)
  if (sg_query_backend() == SG_BACKEND_METAL_MACOS) {
    static sg_shader_desc desc;
    static bool valid;
    if (!valid) {
      valid = true;
      desc.vs.source = sprite_default_vs_source_metal_macos;
      desc.vs.entry = "main0";
      desc.vs.uniform_blocks[0].size = 64;
      desc.fs.source = sprite_default_fs_source_metal_macos;
      desc.fs.entry = "main0";
      desc.fs.uniform_blocks[0].size = 16;
      desc.fs.images[0].name = "u_image";
      desc.fs.images[0].type = SG_IMAGETYPE_2D;
      desc.fs.images[0].sampler_type = SG_SAMPLERTYPE_FLOAT;
      desc.label = "sprite_default_shd_shader";
    };
    return &desc;
  }
  #endif /* SOKOL_METAL */
  return 0; /* can't happen */
}
