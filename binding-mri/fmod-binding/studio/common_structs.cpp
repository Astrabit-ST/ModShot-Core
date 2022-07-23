#include "common_structs.h"
#include "fmod_bindings.h"
#include <fmod_studio.h>

VALUE rb_cMemoryUsage = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_MEMORY_USAGE, rb_cMemoryUsage);
FMOD2RB(exclusive, INT2NUM);
FMOD2RB(inclusive, INT2NUM);
FMOD2RB(sampledata, INT2NUM);
FMOD2RB_END;

VALUE rb_cParameterDescription = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_PARAMETER_DESCRIPTION, rb_cParameterDescription);
FMOD2RB(name, rb_str_new_cstr);
FMOD2RB_STRUCT(id, FMOD_STUDIO_PARAMETER_ID);
FMOD2RB(minimum, DBL2NUM);
FMOD2RB(maximum, DBL2NUM);
FMOD2RB_NAME(default_value, defaultvalue, DBL2NUM);
FMOD2RB(type, INT2NUM);
FMOD2RB(flags, INT2NUM);
FMOD2RB_STRUCT(guid, FMOD_GUID);
FMOD2RB_END;

VALUE rb_cParameterID = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_PARAMETER_ID, rb_cParameterID);
FMOD2RB(data1, UINT2NUM);
FMOD2RB(data2, UINT2NUM);
FMOD2RB_END;

DECLARE_RB2FMOD(FMOD_STUDIO_PARAMETER_ID, rb_cParameterID);
RB2FMOD(data1, NUM2UINT);
RB2FMOD(data2, NUM2UINT);
RB2FMOD_END;

VALUE rb_cUserProperty = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_USER_PROPERTY, rb_cUserProperty);
FMOD2RB(name, rb_str_new_cstr);
FMOD2RB(type, INT2NUM);
switch (p.type)
{
    case FMOD_STUDIO_USER_PROPERTY_TYPE_INTEGER:
        rb_iv_set(self, "@value", INT2NUM(p.intvalue));
        break;
    case FMOD_STUDIO_USER_PROPERTY_TYPE_BOOLEAN:
        rb_iv_set(self, "@value", BOOL2RB(p.boolvalue));
        break;
    case FMOD_STUDIO_USER_PROPERTY_TYPE_FLOAT:
        rb_iv_set(self, "@value", DBL2NUM(p.floatvalue));
        break;
    case FMOD_STUDIO_USER_PROPERTY_TYPE_STRING:
        rb_iv_set(self, "@value", rb_str_new_cstr(p.stringvalue));
        break;
    default:
        rb_raise(rb_eRuntimeError, "User property type is invalid");
        break;
}
FMOD2RB_END;

VALUE rb_cCommandInfo = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_COMMAND_INFO, rb_cCommandInfo);
FMOD2RB_NAME(command_name, commandname, rb_str_new_cstr);
FMOD2RB_NAME(parent_command_index, parentcommandindex, INT2NUM);
FMOD2RB_NAME(frame_number, framenumber, INT2NUM);
FMOD2RB_NAME(frame_time, frametime, DBL2NUM);
FMOD2RB_NAME(instance_type, instancetype, INT2NUM);
FMOD2RB_NAME(output_type, outputtype, INT2NUM);
FMOD2RB_NAME(instance_handle, instancehandle, UINT2NUM);
FMOD2RB_NAME(output_handle, outputhandle, UINT2NUM);
FMOD2RB_END;

VALUE rb_cAdvancedSettings = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_ADVANCEDSETTINGS, rb_cAdvancedSettings);
FMOD2RB_NAME(cb_size, cbsize, INT2NUM);
FMOD2RB_NAME(command_queue_size, commandqueuesize, UINT2NUM);
FMOD2RB_NAME(handle_initial_size, handleinitialsize, UINT2NUM);
FMOD2RB_NAME(studio_update_period, studioupdateperiod, INT2NUM);
FMOD2RB_NAME(idle_sample_data_pool_size, idlesampledatapoolsize, INT2NUM);
FMOD2RB_NAME(streaming_schedule_delay, streamingscheduledelay, UINT2NUM);
FMOD2RB_NAME(encryption_key, encryptionkey, rb_str_new_cstr);
FMOD2RB_END;

DECLARE_RB2FMOD(FMOD_STUDIO_ADVANCEDSETTINGS, rb_cAdvancedSettings);
RB2FMOD_NAME(cb_size, cbsize, NUM2INT);
RB2FMOD_NAME(command_queue_size, commandqueuesize, NUM2UINT);
RB2FMOD_NAME(handle_initial_size, handleinitialsize, NUM2UINT);
RB2FMOD_NAME(studio_update_period, studioupdateperiod, NUM2INT);
RB2FMOD_NAME(idle_sample_data_pool_size, idlesampledatapoolsize, NUM2INT);
RB2FMOD_NAME(streaming_schedule_delay, streamingscheduledelay, NUM2UINT);
RB2FMOD_NAME(encryption_key, encryptionkey, RSTRING_PTR);
RB2FMOD_END;

VALUE rb_cSoundInfo = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_SOUND_INFO, rb_cSoundInfo);
FMOD2RB(name_or_data, rb_str_new_cstr);
FMOD2RB(mode, UINT2NUM);
FMOD2RB_STRUCT_NAME(ex_info, exinfo, FMOD_CREATESOUNDEXINFO);
FMOD2RB_NAME(subsound_index, subsoundindex, INT2NUM);
FMOD2RB_END;

VALUE rb_cStudioCPUUsage = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_CPU_USAGE, rb_cStudioCPUUsage);
FMOD2RB(update, DBL2NUM);
FMOD2RB_END;

VALUE rb_cBufferUsage = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_BUFFER_USAGE, rb_cBufferUsage);
FMOD2RB_STRUCT_NAME(studio_command_queue, studiocommandqueue, FMOD_STUDIO_BUFFER_INFO);
FMOD2RB_STRUCT_NAME(studio_handle, studiohandle, FMOD_STUDIO_BUFFER_INFO);
FMOD2RB_END;

VALUE rb_cBufferInfo = Qnil;
DECLARE_FMOD2RB(FMOD_STUDIO_BUFFER_INFO, rb_cBufferInfo);
FMOD2RB_NAME(current_usage, currentusage, INT2NUM);
FMOD2RB_NAME(peak_usage, peakusage, INT2NUM);
FMOD2RB(capacity, INT2NUM);
FMOD2RB_NAME(stall_count, stallcount, INT2NUM);
FMOD2RB_NAME(stall_time, stalltime, DBL2NUM);
FMOD2RB_END;

void bindFmodStudioStructs()
{
    rb_cMemoryUsage = rb_define_class_under(rb_mFMOD_Studio, "MemoryUsage", rb_cObject);
    ATTR(rb_cMemoryUsage, exclusive);
    ATTR(rb_cMemoryUsage, inclusive);
    ATTR(rb_cMemoryUsage, sampledata);

    rb_cParameterDescription = rb_define_class_under(
        rb_mFMOD_Studio, "ParameterDescription", rb_cObject);
    ATTR(rb_cParameterDescription, name);
    ATTR(rb_cParameterDescription, id);
    ATTR(rb_cParameterDescription, minimum);
    ATTR(rb_cParameterDescription, maximum);
    ATTR(rb_cParameterDescription, default_value);
    ATTR(rb_cParameterDescription, type);
    ATTR(rb_cParameterDescription, flags);
    ATTR(rb_cParameterDescription, guid);

    rb_cParameterID = rb_define_class_under(rb_mFMOD_Studio, "ParameterID", rb_cObject);
    ATTR(rb_cParameterID, data1);
    ATTR(rb_cParameterID, data2);

    rb_cUserProperty = rb_define_class_under(rb_mFMOD_Studio, "UserProperty", rb_cObject);
    ATTR(rb_cUserProperty, name);
    ATTR(rb_cUserProperty, type);
    ATTR(rb_cUserProperty, value);

    rb_cCommandInfo = rb_define_class_under(rb_mFMOD_Studio, "CommandInfo", rb_cObject);
    ATTR(rb_cCommandInfo, command_name);
    ATTR(rb_cCommandInfo, parent_command_index);
    ATTR(rb_cCommandInfo, frame_number);
    ATTR(rb_cCommandInfo, frame_time);
    ATTR(rb_cCommandInfo, instance_type);
    ATTR(rb_cCommandInfo, output_type);
    ATTR(rb_cCommandInfo, instance_handle);
    ATTR(rb_cCommandInfo, output_handle);

    rb_cAdvancedSettings = rb_define_class_under(rb_mFMOD_Studio, "AdvancedSettings", rb_cObject);
    ATTR(rb_cAdvancedSettings, cb_size);
    ATTR(rb_cAdvancedSettings, command_queue_size);
    ATTR(rb_cAdvancedSettings, handle_initial_size);
    ATTR(rb_cAdvancedSettings, studio_update_period);
    ATTR(rb_cAdvancedSettings, idle_sample_data_pool_size);
    ATTR(rb_cAdvancedSettings, streaming_schedule_delay);
    ATTR(rb_cAdvancedSettings, encryption_key);

    rb_cSoundInfo = rb_define_class_under(rb_mFMOD_Studio, "SoundInfo", rb_cObject);
    ATTR(rb_cSoundInfo, name_or_data);
    ATTR(rb_cSoundInfo, mode);
    ATTR(rb_cSoundInfo, ex_info);
    ATTR(rb_cSoundInfo, subsound_index);

    rb_cStudioCPUUsage = rb_define_class_under(rb_mFMOD_Studio, "CPUUsage", rb_cObject);
    ATTR(rb_cStudioCPUUsage, update);

    rb_cBufferUsage = rb_define_class_under(rb_mFMOD_Studio, "BufferUsage", rb_cObject);
    ATTR(rb_cBufferUsage, studio_command_queue);
    ATTR(rb_cBufferUsage, studio_handle);

    rb_cBufferInfo = rb_define_class_under(rb_mFMOD_Studio, "BufferInfo", rb_cObject);
    ATTR(rb_cBufferInfo, current_usage);
    ATTR(rb_cBufferInfo, peak_usage);
    ATTR(rb_cBufferInfo, capacity);
    ATTR(rb_cBufferInfo, stall_count);
    ATTR(rb_cBufferInfo, stall_time);
}
