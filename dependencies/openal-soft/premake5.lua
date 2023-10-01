project "openal"
	removeplatforms("web")
	kind "StaticLib"
	language "C++"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	defines {
		"NDEBUG",
		"ALC_API=''",
		"AL_ALEXT_PROTOTYPES",
		"AL_API=''",
		"AL_BUILD_LIBRARY",
		"AL_LIBTYPE_STATIC",
		"RESTRICT=__restrict",
		"__STDC_FORMAT_MACROS"
	}

	buildoptions {
		"-Os",
		"-std=gnu++17",
		"-Winline",
		"-Wunused",
		"-Wall",
		"-Wextra",
		"-Wshadow",
		"-Wconversion",
		"-Wcast-align",
		"-Wpedantic",
		"-Wnon-virtual-dtor",
		"-Woverloaded-virtual",
		"-Wno-old-style-cast",
		"-Wno-c++20-attribute-extensions",
		"-Wno-deprecated-declarations",
		"-fno-math-errno",
		"-pthread"
	}

	linkoptions {
		"-no_warning_for_no_symbols"
	}

	includedirs {
		".",
		"include",
		"common",
		"config"
	}

	files {
		"common/alcomplex.cpp",
		"common/alfstream.cpp",
		"common/almalloc.cpp",
		"common/alsem.cpp",
		"common/alstring.cpp",
		"common/althrd_setname.cpp",
		"common/dynload.cpp",
		"common/polyphase_resampler.cpp",
		"common/ringbuffer.cpp",
		"common/strutils.cpp",
		"al/auxeffectslot.cpp",
		"al/buffer.cpp",
		"al/debug.cpp",
		"al/effect.cpp",
		"al/effects/autowah.cpp",
		"al/effects/chorus.cpp",
		"al/effects/compressor.cpp",
		"al/effects/convolution.cpp",
		"al/effects/dedicated.cpp",
		"al/effects/distortion.cpp",
		"al/effects/echo.cpp",
		"al/effects/effects.cpp",
		"al/effects/equalizer.cpp",
		"al/effects/fshifter.cpp",
		"al/effects/modulator.cpp",
		"al/effects/null.cpp",
		"al/effects/pshifter.cpp",
		"al/effects/reverb.cpp",
		"al/effects/vmorpher.cpp",
		"al/error.cpp",
		"al/event.cpp",
		"al/extension.cpp",
		"al/filter.cpp",
		"al/listener.cpp",
		"al/source.cpp",
		"al/state.cpp",
		"alc/alc.cpp",
		"alc/alu.cpp",
		"alc/alconfig.cpp",
		"alc/context.cpp",
		"alc/device.cpp",
		"alc/effects/autowah.cpp",
		"alc/effects/chorus.cpp",
		"alc/effects/compressor.cpp",
		"alc/effects/convolution.cpp",
		"alc/effects/dedicated.cpp",
		"alc/effects/distortion.cpp",
		"alc/effects/echo.cpp",
		"alc/effects/equalizer.cpp",
		"alc/effects/fshifter.cpp",
		"alc/effects/modulator.cpp",
		"alc/effects/null.cpp",
		"alc/effects/pshifter.cpp",
		"alc/effects/reverb.cpp",
		"alc/effects/vmorpher.cpp",
		"alc/events.cpp",
		"alc/panning.cpp",
		"alc/backends/base.cpp",
		"alc/backends/loopback.cpp",
		"alc/backends/null.cpp",
		"alc/backends/coreaudio.cpp",
		"alc/backends/portaudio.cpp",
		"alc/backends/wave.cpp",
		"core/ambdec.cpp",
		"core/ambidefs.cpp",
		"core/bformatdec.cpp",
		"core/bs2b.cpp",
		"core/bsinc_tables.cpp",
		"core/buffer_storage.cpp",
		"core/context.cpp",
		"core/converter.cpp",
		"core/cpu_caps.cpp",
		"core/cubic_tables.cpp",
		"core/devformat.cpp",
		"core/device.cpp",
		"core/effectslot.cpp",
		"core/except.cpp",
		"core/filters/biquad.cpp",
		"core/filters/nfc.cpp",
		"core/filters/splitter.cpp",
		"core/fmt_traits.cpp",
		"core/fpu_ctrl.cpp",
		"core/helpers.cpp",
		"core/hrtf.cpp",
		"core/logging.cpp",
		"core/mastering.cpp",
		"core/mixer.cpp",
		"core/uhjfilter.cpp",
		"core/uiddefs.cpp",
		"core/voice.cpp",
		"core/mixer/mixer_c.cpp",
		"core/mixer/mixer_sse.cpp",
		"core/mixer/mixer_sse2.cpp",
		"core/mixer/mixer_sse3.cpp",
		"core/mixer/mixer_sse41.cpp"
	}