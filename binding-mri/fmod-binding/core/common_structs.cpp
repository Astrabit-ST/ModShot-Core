#include "common_structs.h"
#include "fmod_bindings.h"
#include <fmod_studio.h>

VALUE rb_cGUID = Qnil;

DECLARE_FMOD2RB(FMOD_GUID, rb_cGUID);
FMOD2RB_NAME(data1, Data1, UINT2NUM);
FMOD2RB_NAME(data2, Data2, UINT2NUM);
FMOD2RB_NAME(data3, Data3, UINT2NUM);
FMOD2RB_CAST(data4, Data4, char*, rb_str_new_cstr);
FMOD2RB_END;

DECLARE_RB2FMOD(FMOD_GUID, rb_cGUID);
RB2FMOD_NAME(data1, Data1, NUM2UINT);
RB2FMOD_NAME(data2, Data2, NUM2UINT);
RB2FMOD_NAME(data3, Data3, NUM2UINT);
if (RSTRING_LEN(rb_iv_get(self, "@data4")) != 8)
{
    rb_raise(rb_eArgError, "data4 must be 8 bytes long");
}
strcpy((char*) p.Data4, RSTRING_PTR(rb_iv_get(self, "@data4"))); //! BAD UNSAFE BAD
RB2FMOD_END;

VALUE rb_c3D_Attributes = Qnil;
DECLARE_FMOD2RB(FMOD_3D_ATTRIBUTES, rb_c3D_Attributes);
FMOD2RB_STRUCT(position, FMOD_VECTOR);
FMOD2RB_STRUCT(velocity, FMOD_VECTOR);
FMOD2RB_STRUCT(forward, FMOD_VECTOR);
FMOD2RB_STRUCT(up, FMOD_VECTOR);
FMOD2RB_END;

DECLARE_RB2FMOD(FMOD_3D_ATTRIBUTES, rb_c3D_Attributes);
RB2FMOD_STRUCT(position, FMOD_VECTOR);
RB2FMOD_STRUCT(velocity, FMOD_VECTOR);
RB2FMOD_STRUCT(forward, FMOD_VECTOR);
RB2FMOD_STRUCT(up, FMOD_VECTOR);
RB2FMOD_END;

VALUE rb_cVector = Qnil;
DECLARE_FMOD2RB(FMOD_VECTOR, rb_cVector);
FMOD2RB(x, DBL2NUM);
FMOD2RB(y, DBL2NUM);
FMOD2RB(z, DBL2NUM);
FMOD2RB_END;

DECLARE_RB2FMOD(FMOD_VECTOR, rb_cVector);
RB2FMOD(x, NUM2DBL);
RB2FMOD(y, NUM2DBL);
RB2FMOD(z, NUM2DBL);
RB2FMOD_END;

//! Holy fuck
VALUE rb_cCreateSoundExInfo = Qnil;
DECLARE_FMOD2RB(FMOD_CREATESOUNDEXINFO, rb_cCreateSoundExInfo);
FMOD2RB_NAME(cb_size, cbsize, INT2NUM);
FMOD2RB(length, UINT2NUM);
FMOD2RB_NAME(file_offset, fileoffset, UINT2NUM);
FMOD2RB_NAME(num_channels, numchannels, INT2NUM);
FMOD2RB_NAME(default_frequency, defaultfrequency, INT2NUM);
FMOD2RB(format, INT2NUM);
FMOD2RB_NAME(decode_buffer_size, decodebuffersize, UINT2NUM);
FMOD2RB_NAME(initial_subsound, initialsubsound, INT2NUM);
FMOD2RB_NAME(num_subsounds, numsubsounds, INT2NUM);
VALUE inclusion_list = rb_ary_new();
for (int i = 0; i < p.numsubsounds; i++)
{
    rb_ary_push(inclusion_list, INT2NUM(p.inclusionlist[i]));
}
rb_iv_set(self, "@inclusion_list", inclusion_list);
FMOD2RB_NAME(inclusion_list_num, inclusionlistnum, INT2NUM);
rb_iv_set(self, "@pcm_read_callback", Qnil); // TODO
rb_iv_set(self, "@pcm_set_pos_callback", Qnil); // TODO
rb_iv_set(self, "@nonblock_callback", Qnil); // TODO
FMOD2RB_NAME(dls_name, dlsname, rb_str_new_cstr);
FMOD2RB_NAME(encryption_key, encryptionkey, rb_str_new_cstr);
FMOD2RB_NAME(max_poly_phony, maxpolyphony, INT2NUM);
rb_iv_set(self, "@userdata", Qnil); // TODO
FMOD2RB_NAME(suggested_sound_type, suggestedsoundtype, INT2NUM);
rb_iv_set(self, "@file_user_open", Qnil); // TODO
rb_iv_set(self, "@file_user_close", Qnil); // TODO
rb_iv_set(self, "@file_user_read", Qnil); // TODO
rb_iv_set(self, "@file_user_seek", Qnil); // TODO
rb_iv_set(self, "@file_user_async_read", Qnil); // TODO
rb_iv_set(self, "@file_user_async_cancel", Qnil); // TODO
rb_iv_set(self, "@file_user_data", Qnil); // TODO
FMOD2RB_NAME(file_buffer_size, filebuffersize, INT2NUM);
FMOD2RB_NAME(channel_order, channelorder, INT2NUM);
rb_iv_set(self, "@channel_group", Qnil); // TODO
FMOD2RB_NAME(initial_seek_position, initialseekposition, UINT2NUM);
FMOD2RB_NAME(initial_seek_pos_type, initialseekpostype, UINT2NUM);
FMOD2RB_NAME(ignore_set_filesystem, ignoresetfilesystem, INT2NUM);
FMOD2RB_NAME(audio_queue_policy, audioqueuepolicy, UINT2NUM);
FMOD2RB_NAME(min_midi_granularity, minmidigranularity, UINT2NUM);
FMOD2RB_NAME(nonblock_thread_id, nonblockthreadid, INT2NUM);
if (p.fsbguid) {
    rb_iv_set(self, "@fsb_guid", fmodFMOD_GUID2rb(*p.fsbguid)); // FIXME: Probably not right
}
FMOD2RB_END;

VALUE rb_cCPUUsage = Qnil;
DECLARE_FMOD2RB(FMOD_CPU_USAGE, rb_cCPUUsage);
FMOD2RB(dsp, DBL2NUM);
FMOD2RB(stream, DBL2NUM);
FMOD2RB(geometry, DBL2NUM);
FMOD2RB(update, DBL2NUM);
FMOD2RB(convolution1, DBL2NUM);
FMOD2RB(convolution2, DBL2NUM);
FMOD2RB_END;

void bindFmodCoreStructs()
{
    rb_cGUID = rb_define_class_under(rb_mFMOD_Core, "GUID", rb_cObject);
    ATTR(rb_cGUID, data1);
    ATTR(rb_cGUID, data2);
    ATTR(rb_cGUID, data3);
    ATTR(rb_cGUID, data4);

    rb_c3D_Attributes = rb_define_class_under(rb_mFMOD_Core, "_3DAttributes", rb_cObject);
    ATTR(rb_c3D_Attributes, position);
    ATTR(rb_c3D_Attributes, velocity);
    ATTR(rb_c3D_Attributes, forward);
    ATTR(rb_c3D_Attributes, up);

    rb_cVector = rb_define_class_under(rb_mFMOD_Core, "Vector", rb_cObject);
    ATTR(rb_cVector, x);
    ATTR(rb_cVector, y);
    ATTR(rb_cVector, z);

    rb_cCreateSoundExInfo = rb_define_class_under(rb_mFMOD_Core, "CreateSoundExInfo", rb_cObject);
    ATTR(rb_cCreateSoundExInfo, cb_size);
    ATTR(rb_cCreateSoundExInfo, length);
    ATTR(rb_cCreateSoundExInfo, file_offset);
    ATTR(rb_cCreateSoundExInfo, num_channels);
    ATTR(rb_cCreateSoundExInfo, default_frequency);
    ATTR(rb_cCreateSoundExInfo, format);
    ATTR(rb_cCreateSoundExInfo, decode_buffer_size);
    ATTR(rb_cCreateSoundExInfo, initial_subsound);
    ATTR(rb_cCreateSoundExInfo, num_subsounds);
    ATTR(rb_cCreateSoundExInfo, inclusion_list);
    ATTR(rb_cCreateSoundExInfo, inclusion_list_num);
    ATTR(rb_cCreateSoundExInfo, pcm_read_callback);
    ATTR(rb_cCreateSoundExInfo, pcm_set_pos_callback);
    ATTR(rb_cCreateSoundExInfo, nonblock_callback);
    ATTR(rb_cCreateSoundExInfo, dls_name);
    ATTR(rb_cCreateSoundExInfo, encryption_key);
    ATTR(rb_cCreateSoundExInfo, max_poly_phony);
    ATTR(rb_cCreateSoundExInfo, userdata);
    ATTR(rb_cCreateSoundExInfo, suggested_sound_type);
    ATTR(rb_cCreateSoundExInfo, file_user_open);
    ATTR(rb_cCreateSoundExInfo, file_user_close);
    ATTR(rb_cCreateSoundExInfo, file_user_read);
    ATTR(rb_cCreateSoundExInfo, file_user_seek);
    ATTR(rb_cCreateSoundExInfo, file_user_async_read);
    ATTR(rb_cCreateSoundExInfo, file_user_async_cancel);
    ATTR(rb_cCreateSoundExInfo, file_user_data);
    ATTR(rb_cCreateSoundExInfo, file_buffer_size);
    ATTR(rb_cCreateSoundExInfo, channel_order);
    ATTR(rb_cCreateSoundExInfo, channel_group);
    ATTR(rb_cCreateSoundExInfo, initial_seek_position);
    ATTR(rb_cCreateSoundExInfo, initial_seek_pos_type);
    ATTR(rb_cCreateSoundExInfo, ignore_set_filesystem);
    ATTR(rb_cCreateSoundExInfo, audio_queue_policy);
    ATTR(rb_cCreateSoundExInfo, min_midi_granularity);
    ATTR(rb_cCreateSoundExInfo, nonblock_thread_id);
    ATTR(rb_cCreateSoundExInfo, fsb);

    rb_cCPUUsage = rb_define_class_under(rb_mFMOD_Core, "CPUUsage", rb_cObject);
    ATTR(rb_cCPUUsage, dsp);
    ATTR(rb_cCPUUsage, stream);
    ATTR(rb_cCPUUsage, geometry);
    ATTR(rb_cCPUUsage, update);
    ATTR(rb_cCPUUsage, convolution1);
    ATTR(rb_cCPUUsage, convolution2);
}
