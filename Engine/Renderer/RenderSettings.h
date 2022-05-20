#ifndef RENDERSETTINGS_H
#define RENDERSETTINGS_H

#include "Core/Interfaces/Object.h"

#include <string>
#include <glm/vec2.hpp>

struct Resolution
{
	std::size_t width;
	std::size_t height;
};

struct Viewport
{
	std::size_t x;
	std::size_t y;
	std::size_t width;
	std::size_t height;
};

struct RenderSettings : public Object
{
	std::string name;

	std::string renderMode;
	Resolution resolution;
	Viewport viewport;

	bool indirect_diffuse_enabled;
	bool indirect_specular_enabled;
	bool subsurface_scattering_enabled;
	bool ambient_occlusion_enabled;

	bool ssao_enabled;
	float ssao_scale;
	std::size_t ssao_samples;
	std::size_t ssao_noise_size;
	float ssao_radius;
	float ssao_bias;
	bool ssao_blur_enabled;
	bool ssao_temporal_filter_enabled;

	bool ssr_enabled;
	float ssr_scale;
	std::size_t ssr_iterations;
	float ssr_roughness;
	float ssr_thickness;
	std::size_t ssr_stride;
	float ssr_intensity;

	bool sst_enabled;
	std::size_t sst_iterations;
	float sst_thickness;
	float sst_intensity;

	bool taa_enabled;

	bool vol_lighting_enabled;
	std::size_t vol_lighting_iterations;
	float vol_lighting_scattering;
	float vol_lighting_intensity;

	bool light_shafts_enabled;
	std::size_t light_shafts_iterations;
	float light_shafts_density;
	float light_shafts_weight;
	float light_shafts_decay;
	float light_shafts_intensity;

	bool bloom_enabled;
	float bloom_scale;
	float bloom_threshold;
	float bloom_intensity;

	bool hdr_enabled;
	float hdr_exposure;

	bool lut_enabled;
	std::string lut_texture_path;
	float lut_intensity;

	bool gamma_enabled;

	float rsm_scale;
	std::size_t rsm_samples;
	float rsm_radius;
	bool rsm_ao_enabled;
	float rsm_indirect_diffuse_intensity;
	float rsm_indirect_specular_intensity;
	float rsm_indirect_refractive_intensity;
	std::size_t rsm_reflection_iterations;
	float rsm_reflection_thickness;
	std::size_t rsm_refraction_iterations;
	float rsm_refraction_thickness;
	float rsm_interpolation_scale;
	float rsm_min_interpolation_distance;
	float rsm_min_interpolation_angle;
	bool rsm_debug_interpolation;

	std::size_t trsm_samples;
	float trsm_indirect_diffuse_intensity;
	bool trsm_temporal_filter_enabled;
	bool trsm_blur_enabled;

	std::size_t lpv_volume_size;
	std::size_t lpv_iterations;
	float lpv_injection_bias;
	bool lpv_geometry_occlusion;
	float lpv_indirect_diffuse_intensity;
	float lpv_indirect_specular_intensity;
	float lpv_indirect_refractive_intensity;
	std::size_t lpv_reflection_iterations;
	std::size_t lpv_refraction_iterations;
	bool lpv_emissive_voxelization;
	float lpv_emissive_normal_angle_step;
	std::size_t lpv_emissive_vpls;
	bool lpv_emissive_cache;
	bool lpv_emissive_textured;
	bool lpv_debug_cells;

	std::size_t vct_voxels_size;
	bool vct_continuous_voxelization;
	bool vct_bordering;
	std::size_t vct_mipmap_levels;
	float vct_indirect_diffuse_intensity;
	float vct_indirect_specular_intensity;
	float vct_indirect_refractive_intensity;
	float vct_diffuse_cone_distance;
	float vct_diffuse_origin_bias;
	float vct_specular_cone_ratio;
	float vct_specular_cone_distance;
	float vct_specular_origin_bias;
	float vct_refractive_cone_ratio;
	float vct_refractive_cone_distance;
	bool vct_ao_enabled;
	float vct_ao_cone_ratio;
	float vct_ao_cone_distance;
	bool vct_shadow_cone_enabled;
	float vct_shadow_cone_ratio;
	float vct_shadow_cone_distance;
	float vct_origin_bias;
	bool vct_temporal_filter_enabled;
	bool vct_debug_show_voxels;
	std::size_t vct_debug_volume_mipmap_level;

	bool ssdo_enabled;
	bool ssdo_temporal_filter_enabled;
	float ssdo_scale;
	std::size_t ssdo_samples;
	float ssdo_radius;
	float ssdo_bias;
	float ssdo_sampling_scale;
	std::size_t ssdo_shadow_stride;
	float ssdo_indirect_intensity;
	bool ssdo_ray_shadow;
	float ssdo_shadow_scale;
	bool ssdo_interpolation_enabled;
	float ssdo_interpolation_scale;
	float ssdo_min_interpolation_distance;
	float ssdo_min_interpolation_angle;
	bool ssdo_debug_interpolation;

	bool hgi_temporal_filter_enabled;
	std::size_t hgi_rsm_samples;
	float hgi_rsm_radius;
	std::size_t hgi_ssdo_samples;
	float hgi_ssdo_radius;
	float hgi_rsm_indirect_diffuse_intensity;
	float hgi_ssdo_indirect_diffuse_intensity;
	float hgi_ssdo_sampling_scale;
	bool hgi_interpolation_enabled;
	float hgi_interpolation_scale;
	float hgi_min_interpolation_distance;
	float hgi_min_interpolation_angle;
	bool hgi_debug_interpolation;
	float hgi_rsm_thickness;
	float hgi_rsm_indirect_specular_intensity;
	float hgi_ssr_indirect_specular_intensity;
	bool hgi_ao_enabled;
	std::size_t hgi_ao_samples;
	float hgi_ao_radius;
	float hgi_ao_bias;
	float hgi_ao_blend;

	float ssdgi_intensity;
	std::size_t ssdgi_sample_count;
	float ssdgi_sampling_radius;

	std::size_t ssr_iteration_count;
	float ssr_iteration_step;
	float ssr_sample_thickness;
};

#endif