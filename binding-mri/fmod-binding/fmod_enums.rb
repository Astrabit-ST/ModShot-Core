module FMOD
  module Core
    module DebugFlags
      LEVEL_NONE = 0x00000000
      LEVEL_ERROR = 0x00000001
      LEVEL_WARNING = 0x00000002
      LEVEL_LOG = 0x00000004
      TYPE_MEMORY = 0x00000100
      TYPE_FILE = 0x00000200
      TYPE_CODEC = 0x00000400
      TYPE_TRACE = 0x00000800
      DISPLAY_TIMESTAMPS = 0x00010000
      DISPLAY_LINENUMBERS = 0x00020000
      DISPLAY_THREAD = 0x00040000
    end

    module MemoryType
      NORMAL = 0x00000000
      STREAM_FILE = 0x00000001
      STREAM_DECODE = 0x00000002
      SAMPLEDATA = 0x00000004
      DSP_BUFFER = 0x00000008
      PLUGIN = 0x00000010
      PERSISTENT = 0x00200000
      ALL = 0xFFFFFFFF
    end

    module InitFlags
      NORMAL = 0x00000000
      STREAM_FROM_UPDATE = 0x00000001
      MIX_FROM_UPDATE = 0x00000002
      _3D_RIGHTHANDED = 0x00000004
      CHANNEL_LOWPASS = 0x00000100
      CHANNEL_DISTANCEFILTER = 0x00000200
      PROFILE_ENABLE = 0x00010000
      VOL0_BECOMES_VIRTUAL = 0x00020000
      GEOMETRY_USECLOSEST = 0x00040000
      PREFER_DOLBY_DOWNMIX = 0x00080000
      THREAD_UNSAFE = 0x00100000
      PROFILE_METER_ALL = 0x00200000
      MEMORY_TRACKING = 0x00400000
    end

    module DriverState
      CONNECTED = 0x00000001
      DEFAULT = 0x00000002
    end

    module TimeUnit
      MS = 0x00000001
      PCM = 0x00000002
      PCMBYTES = 0x00000004
      RAWBYTES = 0x00000008
      PCMFRACTION = 0x00000010
      MODORDER = 0x00000100
      MODROW = 0x00000200
      MODPATTERN = 0x00000400
    end

    module SystemCallbackType
      DEVICELISTCHANGED = 0x00000001
      DEVICELOST = 0x00000002
      MEMORYALLOCATIONFAILED = 0x00000004
      THREADCREATED = 0x00000008
      BADDSPCONNECTION = 0x00000010
      PREMIX = 0x00000020
      POSTMIX = 0x00000040
      ERROR = 0x00000080
      MIDMIX = 0x00000100
      THREADDESTROYED = 0x00000200
      PREUPDATE = 0x00000400
      POSTUPDATE = 0x00000800
      RECORDLISTCHANGED = 0x00001000
      BUFFEREDNOMIX = 0x00002000
      DEVICEREINITIALIZE = 0x00004000
      OUTPUTUNDERRUN = 0x00008000
      ALL = 0xFFFFFFFF
    end

    module Mode
      DEFAULT = 0x00000000
      LOOP_OFF = 0x00000001
      LOOP_NORMAL = 0x00000002
      LOOP_BIDI = 0x00000004
      _2D = 0x00000008
      _3D = 0x00000010
      CREATESTREAM = 0x00000080
      CREATESAMPLE = 0x00000100
      CREATECOMPRESSEDSAMPLE = 0x00000200
      OPENUSER = 0x00000400
      OPENMEMORY = 0x00000800
      OPENMEMORY_POINT = 0x10000000
      OPENRAW = 0x00001000
      OPENONLY = 0x00002000
      ACCURATETIME = 0x00004000
      MPEGSEARCH = 0x00008000
      NONBLOCKING = 0x00010000
      UNIQUE = 0x00020000
      _3D_HEADRELATIVE = 0x00040000
      _3D_WORLDRELATIVE = 0x00080000
      _3D_INVERSEROLLOFF = 0x00100000
      _3D_LINEARROLLOFF = 0x00200000
      _3D_LINEARSQUAREROLLOFF = 0x00400000
      _3D_INVERSETAPEREDROLLOFF = 0x00800000
      _3D_CUSTOMROLLOFF = 0x04000000
      _3D_IGNOREGEOMETRY = 0x40000000
      IGNORETAGS = 0x02000000
      LOWMEM = 0x08000000
      VIRTUAL_PLAYFROMSTART = 0x80000000
    end

    module ChannelMask
      FRONT_LEFT = 0x00000001
      FRONT_RIGHT = 0x00000002
      FRONT_CENTER = 0x00000004
      LOW_FREQUENCY = 0x00000008
      SURROUND_LEFT = 0x00000010
      SURROUND_RIGHT = 0x00000020
      BACK_LEFT = 0x00000040
      BACK_RIGHT = 0x00000080
      BACK_CENTER = 0x00000100

      MONO = (FRONT_LEFT)
      STEREO = (FRONT_LEFT | FRONT_RIGHT)
      LRC = (FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER)
      QUAD = (FRONT_LEFT | FRONT_RIGHT | SURROUND_LEFT | SURROUND_RIGHT)
      SURROUND = (FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER | SURROUND_LEFT | SURROUND_RIGHT)
      _5POINT1 = (FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER | LOW_FREQUENCY | SURROUND_LEFT | SURROUND_RIGHT)
      _5POINT1_REARS = (FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER | LOW_FREQUENCY | BACK_LEFT | BACK_RIGHT)
      _7POINT0 = (FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER | SURROUND_LEFT | SURROUND_RIGHT | BACK_LEFT | BACK_RIGHT)
      _7POINT1 = (FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER | LOW_FREQUENCY | SURROUND_LEFT | SURROUND_RIGHT | BACK_LEFT | BACK_RIGHT)
    end

    module ThreadPriority
      PLATFORM_MIN = (-32 * 1024)
      PLATFORM_MAX = (32 * 1024)

      DEFAULT = (PLATFORM_MIN - 1)
      LOW = (PLATFORM_MIN - 2)
      MEDIUM = (PLATFORM_MIN - 3)
      HIGH = (PLATFORM_MIN - 4)
      VERY_HIGH = (PLATFORM_MIN - 5)
      EXTREME = (PLATFORM_MIN - 6)
      CRITICAL = (PLATFORM_MIN - 7)

      MIXER = EXTREME
      FEEDER = CRITICAL
      STREAM = VERY_HIGH
      FILE = HIGH
      NONBLOCKING = HIGH
      RECORD = HIGH
      GEOMETRY = LOW
      PROFILER = MEDIUM
      STUDIO_UPDATE = MEDIUM
      STUDIO_LOAD_BANK = MEDIUM
      STUDIO_LOAD_SAMPLE = MEDIUM
      CONVOLUTION1 = VERY_HIGH
      CONVOLUTION2 = VERY_HIGH
    end

    module ThreadStackSize
      DEFAULT = 0
      MIXER = (80 * 1024)
      FEEDER = (16 * 1024)
      STREAM = (96 * 1024)
      FILE = (64 * 1024)
      NONBLOCKING = (112 * 1024)
      RECORD = (16 * 1024)
      GEOMETRY = (48 * 1024)
      PROFILER = (128 * 1024)
      STUDIO_UPDATE = (96 * 1024)
      STUDIO_LOAD_BANK = (96 * 1024)
      STUDIO_LOAD_SAMPLE = (96 * 1024)
      CONVOLUTION1 = (16 * 1024)
      CONVOLUTION2 = (16 * 1024)
    end

    module ThreadAffinity
      GROUP_DEFAULT = 0x4000000000000000
      GROUP_A = 0x4000000000000001
      GROUP_B = 0x4000000000000002
      GROUP_C = 0x4000000000000003

      MIXER = GROUP_A
      FEEDER = GROUP_C
      STREAM = GROUP_C
      FILE = GROUP_C
      NONBLOCKING = GROUP_C
      RECORD = GROUP_C
      GEOMETRY = GROUP_C
      PROFILER = GROUP_C
      STUDIO_UPDATE = GROUP_B
      STUDIO_LOAD_BANK = GROUP_C
      STUDIO_LOAD_SAMPLE = GROUP_C
      CONVOLUTION1 = GROUP_C
      CONVOLUTION2 = GROUP_C

      CORE_ALL = 0
      CORE_0 = (1 << 0)
      CORE_1 = (1 << 1)
      CORE_2 = (1 << 2)
      CORE_3 = (1 << 3)
      CORE_4 = (1 << 4)
      CORE_5 = (1 << 5)
      CORE_6 = (1 << 6)
      CORE_7 = (1 << 7)
      CORE_8 = (1 << 8)
      CORE_9 = (1 << 9)
      CORE_10 = (1 << 10)
      CORE_11 = (1 << 11)
      CORE_12 = (1 << 12)
      CORE_13 = (1 << 13)
      CORE_14 = (1 << 14)
      CORE_15 = (1 << 15)
    end

    module Preset
      OFF = [1000, 7, 11, 5000, 100, 100, 100, 250, 0, 20, 96, -80.0]
      GENERIC = [1500, 7, 11, 5000, 83, 100, 100, 250, 0, 14500, 96, -8.0]
      PADDEDCELL = [170, 1, 2, 5000, 10, 100, 100, 250, 0, 160, 84, -7.8]
      ROOM = [400, 2, 3, 5000, 83, 100, 100, 250, 0, 6050, 88, -9.4]
      BATHROOM = [1500, 7, 11, 5000, 54, 100, 60, 250, 0, 2900, 83, 0.5]
      LIVINGROOM = [500, 3, 4, 5000, 10, 100, 100, 250, 0, 160, 58, -19.0]
      STONEROOM = [2300, 12, 17, 5000, 64, 100, 100, 250, 0, 7800, 71, -8.5]
      AUDITORIUM = [4300, 20, 30, 5000, 59, 100, 100, 250, 0, 5850, 64, -11.7]
      CONCERTHALL = [3900, 20, 29, 5000, 70, 100, 100, 250, 0, 5650, 80, -9.8]
      CAVE = [2900, 15, 22, 5000, 100, 100, 100, 250, 0, 20000, 59, -11.3]
      ARENA = [7200, 20, 30, 5000, 33, 100, 100, 250, 0, 4500, 80, -9.6]
      HANGAR = [10000, 20, 30, 5000, 23, 100, 100, 250, 0, 3400, 72, -7.4]
      CARPETTEDHALLWAY = [300, 2, 30, 5000, 10, 100, 100, 250, 0, 500, 56, -24.0]
      HALLWAY = [1500, 7, 11, 5000, 59, 100, 100, 250, 0, 7800, 87, -5.5]
      STONECORRIDOR = [270, 13, 20, 5000, 79, 100, 100, 250, 0, 9000, 86, -6.0]
      ALLEY = [1500, 7, 11, 5000, 86, 100, 100, 250, 0, 8300, 80, -9.8]
      FOREST = [1500, 162, 88, 5000, 54, 79, 100, 250, 0, 760, 94, -12.3]
      CITY = [1500, 7, 11, 5000, 67, 50, 100, 250, 0, 4050, 66, -26.0]
      MOUNTAINS = [1500, 300, 100, 5000, 21, 27, 100, 250, 0, 1220, 82, -24.0]
      QUARRY = [1500, 61, 25, 5000, 83, 100, 100, 250, 0, 3400, 100, -5.0]
      PLAIN = [1500, 179, 100, 5000, 50, 21, 100, 250, 0, 1670, 65, -28.0]
      PARKINGLOT = [1700, 8, 12, 5000, 100, 100, 100, 250, 0, 20000, 56, -19.5]
      SEWERPIPE = [2800, 14, 21, 5000, 14, 80, 60, 250, 0, 3400, 66, 1.2]
      UNDERWATER = [1500, 7, 11, 5000, 10, 100, 100, 250, 0, 500, 92, 7.0]
    end

    MAX_CHANNEL_WIDTH = 32
    MAX_SYSTEMS = 8
    MAX_LISTENERS = 8
    REVERB_MAXINSTANCES = 4
    PORT_INDEX_NONE = 0xFFFFFFFFFFFFFFFF

    FORCEINT = 65536

    module ThreadType
      %w[
        MIXER
        FEEDER
        STREAM
        FILE
        NONBLOCKING
        RECORD
        GEOMETRY
        PROFILER
        STUDIO_UPDATE
        STUDIO_LOAD_BANK
        STUDIO_LOAD_SAMPLE
        CONVOLUTION1
        CONVOLUTION2
      ].each_with_index do |const, i|
        self.const_set(const, i)
      end
    end

    module Result
      %w[
        OK
        ERR_BADCOMMAND
        ERR_CHANNEL_ALLOC
        ERR_CHANNEL_STOLEN
        ERR_DMA
        ERR_DSP_CONNECTION
        ERR_DSP_DONTPROCESS
        ERR_DSP_FORMAT
        ERR_DSP_INUSE
        ERR_DSP_NOTFOUND
        ERR_DSP_RESERVED
        ERR_DSP_SILENCE
        ERR_DSP_TYPE
        ERR_FILE_BAD
        ERR_FILE_COULDNOTSEEK
        ERR_FILE_DISKEJECTED
        ERR_FILE_EOF
        ERR_FILE_ENDOFDATA
        ERR_FILE_NOTFOUND
        ERR_FORMAT
        ERR_HEADER_MISMATCH
        ERR_HTTP
        ERR_HTTP_ACCESS
        ERR_HTTP_PROXY_AUTH
        ERR_HTTP_SERVER_ERROR
        ERR_HTTP_TIMEOUT
        ERR_INITIALIZATION
        ERR_INITIALIZED
        ERR_INTERNAL
        ERR_INVALID_FLOAT
        ERR_INVALID_HANDLE
        ERR_INVALID_PARAM
        ERR_INVALID_POSITION
        ERR_INVALID_SPEAKER
        ERR_INVALID_SYNCPOINT
        ERR_INVALID_THREAD
        ERR_INVALID_VECTOR
        ERR_MAXAUDIBLE
        ERR_MEMORY
        ERR_MEMORY_CANTPOINT
        ERR_NEEDS3D
        ERR_NEEDSHARDWARE
        ERR_NET_CONNECT
        ERR_NET_SOCKET_ERROR
        ERR_NET_URL
        ERR_NET_WOULD_BLOCK
        ERR_NOTREADY
        ERR_OUTPUT_ALLOCATED
        ERR_OUTPUT_CREATEBUFFER
        ERR_OUTPUT_DRIVERCALL
        ERR_OUTPUT_FORMAT
        ERR_OUTPUT_INIT
        ERR_OUTPUT_NODRIVERS
        ERR_PLUGIN
        ERR_PLUGIN_MISSING
        ERR_PLUGIN_RESOURCE
        ERR_PLUGIN_VERSION
        ERR_RECORD
        ERR_REVERB_CHANNELGROUP
        ERR_REVERB_INSTANCE
        ERR_SUBSOUNDS
        ERR_SUBSOUND_ALLOCATED
        ERR_SUBSOUND_CANTMOVE
        ERR_TAGNOTFOUND
        ERR_TOOMANYCHANNELS
        ERR_TRUNCATED
        ERR_UNIMPLEMENTED
        ERR_UNINITIALIZED
        ERR_UNSUPPORTED
        ERR_VERSION
        ERR_EVENT_ALREADY_LOADED
        ERR_EVENT_LIVEUPDATE_BUSY
        ERR_EVENT_LIVEUPDATE_MISMA
        ERR_EVENT_LIVEUPDATE_TIMEO
        ERR_EVENT_NOTFOUND
        ERR_STUDIO_UNINITIALIZED
        ERR_STUDIO_NOT_LOADED
        ERR_INVALID_STRING
        ERR_ALREADY_LOCKED
        ERR_NOT_LOCKED
        ERR_RECORD_DISCONNECTED
        ERR_TOOMANYSAMPLES
      ].each_with_index do |const, i|
        self.const_set(const, i)
      end
    end

    module ChannelControlType
      CHANNEL = 0
      CHANNELGROUP = 1
      MAX = 2
    end

    module OutputType
      %w[
        AUTODETECT
        UNKNOWN
        NOSOUND
        WAVWRITER
        NOSOUND_NRT
        WAVWRITER_NRT
        WASAPI
        ASIO
        PULSEAUDIO
        ALSA
        COREAUDIO
        AUDIOTRACK
        OPENSL
        AUDIOOUT
        AUDIO3D
        WEBAUDIO
        NNAUDIO
        WINSONIC
        AAUDIO
        AUDIOWORKLET
        MAX
      ].each_with_index do |const, i|
        self.const_set(const, i)
      end
    end

    module DebugMode
      TTY = 0
      FILE = 1
      CALLBACK = 2
    end

    module SpeakerMode
      DEFAULT = 0
      RAW = 1
      MONO = 2
      STEREO = 3
      QUAD = 4
      SURROUND = 5
      _5POINT1 = 6
      _7POINT1 = 7
      _7POINT1POINT4 = 8
      MAX = 9
    end

    module Speaker
      %w[
        NONE
        FRONT_LEFT
        FRONT_RIGHT
        FRONT_CENTER
        LOW_FREQUENCY
        SURROUND_LEFT
        SURROUND_RIGHT
        BACK_LEFT
        BACK_RIGHT
        TOP_FRONT_LEFT
        TOP_FRONT_RIGHT
        TOP_BACK_LEFT
        TOP_BACK_RIGHT
        MAX
      ].each_with_index do |const, i|
        self.const_set(const, i - 1)
      end
    end

    module ChannelOrder
      %w[
        DEFAULT
        WAVEFORMAT
        PROTOOLS
        ALLMONO
        ALLSTEREO
        ALSA
        MAX
      ].each_with_index do |const, i|
        self.const_set(const, i)
      end
    end

    module PluginType
      OUTPUT = 0
      CODEC = 1
      DSP = 2
      MAX = 3
    end

    module SoundType
      %w[
        UNKNOWN
        AIFF
        ASF
        DLS
        FLAC
        FSB
        IT
        MIDI
        MOD
        MPEG
        OGGVORBIS
        PLAYLIST
        RAW
        S3M
        USER
        WAV
        XM
        XMA
        AUDIOQUEUE
        AT9
        VORBIS
        MEDIA_FOUND
        MEDIACODEC
        FADPCM
        OPUS
        MAX
      ].each_with_index do |const, i|
        self.const_set(const, i)
      end
    end

    module SoundFormat
      NONE = 0
      PCM8 = 1
      PCM16 = 2
      PCM24 = 3
      PCM32 = 4
      PCMFLOAT = 5
      BITSTREAM = 6
      MAX = 7
    end

    module SoundGroupBehavior
      NORMAL = 0
      MUTE = 1
      STEALLOWEST = 2
      MAX = 3
    end

    module ChannelControlCallbackType
      _END = 0
      VIRTUALVOICE = 1
      SYNCPOINT = 2
      OCCLUSION = 3
      MAX = 4
    end

    module ChannelControlDSPIndex
      HEAD = -1
      FADER = -2
      TAIL = -3
    end

    module ErrorCallbackInstanceType
      %w[
        NONE
        SYSTEM
        CHANNEL
        CHANNELGROUP
        CHANNELCONTROL
        SOUND
        SOUNDGROUP
        DSP
        DSPCONNECTION
        GEOMETRY
        REVERB3D
        STUDIO_SYSTEM
        STUDIO_EVENTDESCRIPTION
        STUDIO_EVENTINSTANCE
        STUDIO_PARAMETERINSTANCE
        STUDIO_BUS
        STUDIO_VCA
        STUDIO_BANK
        STUDIO_COMMANDREPLAY
      ].each_with_index do |const, i|
        self.const_set(const, i)
      end
    end

    module DSPResampler
      DEFAULT = 0
      NOINTERP = 1
      LINEAR = 2
      CUBIC = 3
      SPLINE = 4
      MAX = 5
    end

    module DSPConnectionType
      STANDARD = 0
      SIDECHAIN = 1
      SEND = 2
      SEND_SIDECHAIN = 3
      MAX = 4
    end

    module TagType
      %w[
        UNKNOWN
        ID3V1
        ID3V2
        VORBISCOMMENT
        SHOUTCAST
        ICECAST
        ASF
        MIDI
        PLAYLIST
        FMOD
        USER
        MAX
      ].each_with_index do |const, i|
        self.const_set(const, i)
      end
    end

    module TagDataType
      BINARY = 0
      INT = 1
      FLOAT = 2
      STRING = 3
      STRING_UTF16 = 4
      STRING_UTF16BE = 5
      STRING_UTF8 = 6
      MAX = 7
    end

    module PortType
      MUSIC = 0
      COPYRIGHT_MUSIC = 1
      VOICE = 2
      CONTROLLER = 3
      PERSONA = 4
      VIBRATION = 5
      AUX = 6
      MAX = 7
    end
  end

  module Studio
    LOAD_MEMORY_ALIGNMENT = 32

    module InitFlags
      NORMAL = 0x00000000
      LIVEUPDATE = 0x00000001
      ALLOW_MISSING_PLUGINS = 0x00000002
      SYNCHRONOUS_UPDATE = 0x00000004
      DEFERRED_CALLBACKS = 0x00000008
      LOAD_FROM_UPDATE = 0x00000010
      MEMORY_TRACKING = 0x00000020
    end

    module ParameterFlags
      READONLY = 0x00000001
      AUTOMATIC = 0x00000002
      GLOBAL = 0x00000004
      DISCRETE = 0x00000008
      LABELED = 0x00000010
    end

    module SystemCallbackType
      CALLBACK_PREUPDATE = 0x00000001
      CALLBACK_POSTUPDATE = 0x00000002
      CALLBACK_BANK_UNLOAD = 0x00000004
      CALLBACK_LIVEUPDATE_CONNECTED = 0x00000008
      CALLBACK_LIVEUPDATE_DISCONNECTED = 0x00000010
      CALLBACK_ALL = 0xFFFFFFFF
    end

    module EventCallbackType
      CREATED = 0x00000001
      DESTROYED = 0x00000002
      STARTING = 0x00000004
      STARTED = 0x00000008
      RESTARTED = 0x00000010
      STOPPED = 0x00000020
      START_FAILED = 0x00000040
      CREATE_PROGRAMMER_SOUND = 0x00000080
      DESTROY_PROGRAMMER_SOUND = 0x00000100
      PLUGIN_CREATED = 0x00000200
      PLUGIN_DESTROYED = 0x00000400
      TIMELINE_MARKER = 0x00000800
      TIMELINE_BEAT = 0x00001000
      SOUND_PLAYED = 0x00002000
      SOUND_STOPPED = 0x00004000
      REAL_TO_VIRTUAL = 0x00008000
      VIRTUAL_TO_REAL = 0x00010000
      START_EVENT_COMMAND = 0x00020000
      NESTED_TIMELINE_BEAT = 0x00040000
      ALL = 0xFFFFFFFF
    end

    module LoadBankFlags
      NORMAL = 0x00000000
      NONBLOCKING = 0x00000001
      DECOMPRESS_SAMPLES = 0x00000002
      UNENCRYPTED = 0x00000004
    end

    module CommandCaptureFlags
      NORMAL = 0x00000000
      FILEFLUSH = 0x00000001
      SKIP_INITIAL_STATE = 0x00000002
    end

    module CommandReplayFlags
      NORMAL = 0x00000000
      SKIP_CLEANUP = 0x00000001
      FAST_FORWARD = 0x00000002
      SKIP_BANK_LOAD = 0x00000004
    end

    FORCEINT = 65536

    module LoadingState
      UNLOADING = 0
      UNLOADED = 1
      LOADING = 2
      LOADED = 3
      ERROR = 4
    end

    module LoadMemoryMode
      MEMORY = 0
      MEMORY_POINT = 1
    end

    module ParameterType
      GAME_CONTROLLED = 0
      AUTOMATIC_DISTANCE = 1
      AUTOMATIC_EVENT_CONE_ANGLE = 2
      AUTOMATIC_EVENT_ORIENTATION = 3
      AUTOMATIC_DIRECTION = 4
      AUTOMATIC_ELEVATION = 5
      AUTOMATIC_LISTENER_ORIENTATION = 6
      AUTOMATIC_SPEED = 7
      AUTOMATIC_SPEED_ABSOLUTE = 8
      AUTOMATIC_DISTANCE_NORMALIZED = 9
    end

    module UserPropertyType
      INTEGER = 0
      BOOLEAN = 1
      FLOAT = 2
      STRING = 3
    end

    module EventProperty
      CHANNELPRIORITY = 0
      SCHEDULE_DELAY = 1
      SCHEDULE_LOOKAHEAD = 2
      MINIMUM_DISTANCE = 3
      MAXIMUM_DISTANCE = 4
      COOLDOWN = 5
      MAX = 6
    end

    module PlaybackState
      PLAYING = 0
      SUSTAINING = 1
      STOPPED = 2
      STARTING = 3
      STOPPING = 4
    end

    module StopMode
      ALLOWFADEOUT = 0
      IMMEDIATE = 1
    end

    module InstanceType
      NONE = 0
      SYSTEM = 1
      EVENTDESCRIPTION = 2
      EVENTINSTANCE = 3
      PARAMETERINSTANCE = 4
      BUS = 5
      VCA = 6
      BANK = 7
      COMMANDREPLAY = 8
    end
  end
end
