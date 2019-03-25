/* Copyright (c) 2017-2019 Hans-Kristian Arntzen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "scene.hpp"
#include "scene_formats.hpp"
#include <vector>

namespace Granite
{
class AnimationSystem
{
public:
	void animate(double t);

	void start_animation(Scene::NodeHandle *node_list, const std::string &name, double start_time, bool repeat);
	void start_animation(Scene::Node &node, const std::string &name, double start_time, bool repeat);
	void register_animation(const std::string &name, const SceneFormats::Animation &animation);

private:
	std::unordered_map<std::string, SceneFormats::Animation> animation_map;

	struct AnimationState
	{
		AnimationState(std::vector<std::pair<Transform *, Scene::Node *>> channel_targets_,
		               const SceneFormats::Animation &anim, double start_time_, bool repeating_)
			: channel_targets(std::move(channel_targets_)), animation(anim),
			  start_time(start_time_), repeating(repeating_)
		{
		}
		std::vector<std::pair<Transform *, Scene::Node *>> channel_targets;
		const SceneFormats::Animation &animation;
		double start_time = 0.0;
		bool repeating = false;
	};

	std::vector<std::unique_ptr<AnimationState>> animations;
};
}