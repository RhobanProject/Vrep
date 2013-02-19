% This file is part of the REMOTE API
% 
% Copyright 2006-2013 Dr. Marc Andreas Freese. All rights reserved. 
% marc@coppeliarobotics.com
% www.coppeliarobotics.com
% 
% The REMOTE API is licensed under the terms of GNU GPL:
% 
% -------------------------------------------------------------------
% The REMOTE API is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
% 
% The REMOTE API is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
% 
% You should have received a copy of the GNU General Public License
% along with the REMOTE API.  If not, see <http://www.gnu.org/licenses/>.
% -------------------------------------------------------------------
%
% This file was automatically created for V-REP release V3.0.1 on January 20th 2013

classdef remApi
    
    properties
        libName;
        hFile;
    end
    properties (Constant)
    
		% Scene object types
 		sim_object_shape_type           =0;
		sim_object_joint_type           =1;
		sim_object_graph_type           =2;
		sim_object_camera_type          =3;
		sim_object_dummy_type           =4;
		sim_object_proximitysensor_type =5;
		sim_object_reserved1            =6;
		sim_object_reserved2            =7;
		sim_object_path_type            =8;
		sim_object_visionsensor_type    =9;
		sim_object_volume_type          =10;
		sim_object_mill_type            =11;
		sim_object_forcesensor_type     =12;
		sim_object_light_type           =13;
		sim_object_mirror_type          =14;

		%General object types
		sim_appobj_object_type          =109;
		sim_appobj_collision_type       =110;
		sim_appobj_distance_type        =111;
		sim_appobj_simulation_type      =112;
		sim_appobj_ik_type              =113;
		sim_appobj_constraintsolver_type=114;
		sim_appobj_collection_type      =115;
		sim_appobj_ui_type              =116;
		sim_appobj_script_type          =117;
		sim_appobj_pathplanning_type    =118;
		sim_appobj_RESERVED_type        =119;
		sim_appobj_texture_type         =120;

		% Ik calculation methods
		sim_ik_pseudo_inverse_method        =0;
		sim_ik_damped_least_squares_method  =1;
		sim_ik_jacobian_transpose_method    =2;

		% Ik constraints
		sim_ik_x_constraint         =1;
		sim_ik_y_constraint         =2;
		sim_ik_z_constraint         =4;
		sim_ik_alpha_beta_constraint=8;
		sim_ik_gamma_constraint     =16;
		sim_ik_avoidance_constraint =64;

		% Ik calculation results 
		sim_ikresult_not_performed  =0;
		sim_ikresult_success        =1;
		sim_ikresult_fail           =2;

		% Scene object sub-types 
		sim_light_omnidirectional_subtype   =1;
		sim_light_spot_subtype              =2;
		sim_light_directional_subtype       =3;
		sim_joint_revolute_subtype          =10;
		sim_joint_prismatic_subtype         =11;
		sim_joint_spherical_subtype         =12;
		sim_shape_simpleshape_subtype       =20;
		sim_shape_multishape_subtype        =21;
		sim_proximitysensor_pyramid_subtype =30;
		sim_proximitysensor_cylinder_subtype=31;
		sim_proximitysensor_disc_subtype    =32;
		sim_proximitysensor_cone_subtype    =33;
		sim_proximitysensor_ray_subtype     =34;
		sim_mill_pyramid_subtype            =40;
		sim_mill_cylinder_subtype           =41;
		sim_mill_disc_subtype               =42;
		sim_mill_cone_subtype               =42;
		sim_object_no_subtype               =200;


		%Scene object main properties
		sim_objectspecialproperty_collidable					=1;
		sim_objectspecialproperty_measurable					=2;
		sim_objectspecialproperty_detectable_ultrasonic			=16;
		sim_objectspecialproperty_detectable_infrared			=32;
		sim_objectspecialproperty_detectable_laser				=64;
		sim_objectspecialproperty_detectable_inductive			=128;
		sim_objectspecialproperty_detectable_capacitive			=256;
		sim_objectspecialproperty_renderable					=512;
		sim_objectspecialproperty_detectable_all				=496;
		sim_objectspecialproperty_cuttable						=1024;
		sim_objectspecialproperty_pathplanning_ignored			=2048;

		% Model properties
		sim_modelproperty_not_collidable				=1;
		sim_modelproperty_not_measurable				=2;
		sim_modelproperty_not_renderable				=4;
		sim_modelproperty_not_detectable				=8;
		sim_modelproperty_not_cuttable					=16;
		sim_modelproperty_not_dynamic					=32;
		sim_modelproperty_not_respondable				=64;
		sim_modelproperty_not_reset						=128;
		sim_modelproperty_not_visible					=256;
		sim_modelproperty_not_model						=61440;


		% Check the documentation instead of comments below!! 
		sim_message_ui_button_state_change  =0;	
		sim_message_reserved9               =1;	
		sim_message_object_selection_changed=2;
		sim_message_reserved10				=3;	
		sim_message_model_loaded            =4;
		sim_message_reserved11				=5;	
		sim_message_keypress				=6;	
		sim_message_bannerclicked			=7;	
		sim_message_for_c_api_only_start        =256;  	
		sim_message_reserved1                   =257;  	
		sim_message_reserved2			        =258;  	
		sim_message_reserved3			        =259;  	
		sim_message_eventcallback_scenesave		=260;		
		sim_message_eventcallback_modelsave		=261;      
		sim_message_eventcallback_moduleopen	=262;	    
		sim_message_eventcallback_modulehandle	=263;	    
		sim_message_eventcallback_moduleclose	=264;	    
		sim_message_reserved4					=265;      
		sim_message_reserved5					=266;	    
		sim_message_reserved6					=267;	    
		sim_message_reserved7					=268;	    
		sim_message_eventcallback_instancepass	=269;		
		sim_message_eventcallback_broadcast     =270;
		sim_message_eventcallback_imagefilter_enumreset =271;
		sim_message_eventcallback_imagefilter_enumerate      =272;
		sim_message_eventcallback_imagefilter_adjustparams   =273;
		sim_message_eventcallback_imagefilter_reserved       =274;
		sim_message_eventcallback_imagefilter_process        =275;
		sim_message_eventcallback_reserved1                  =276;  
		sim_message_eventcallback_reserved2                  =277;   
		sim_message_eventcallback_reserved3                  =278;   
		sim_message_eventcallback_reserved4                  =279;   
		sim_message_eventcallback_abouttoundo		         =280;   
		sim_message_eventcallback_undoperformed	             =281;   
		sim_message_eventcallback_abouttoredo		         =282;   
		sim_message_eventcallback_redoperformed	             =283;   
		sim_message_eventcallback_scripticondblclick         =284;   
		sim_message_eventcallback_simulationabouttostart     =285;
		sim_message_eventcallback_simulationended            =286;
		sim_message_eventcallback_reserved5			         =287;   
		sim_message_eventcallback_keypress			         =288;   
		sim_message_eventcallback_modulehandleinsensingpart  =289;   
		sim_message_eventcallback_renderingpass              =290;   
		sim_message_eventcallback_bannerclicked              =291;   
		sim_message_eventcallback_menuitemselected           =292;   
		sim_message_eventcallback_refreshdialogs             =293;   
		sim_message_eventcallback_sceneloaded                =294;
		sim_message_eventcallback_modelloaded                =295;
		sim_message_eventcallback_instanceswitch             =296;
		sim_message_eventcallback_guipass                    =297;
		sim_message_eventcallback_mainscriptabouttobecalled  =298;
		sim_message_eventcallback_rmlposition                =299;   
		sim_message_eventcallback_rmlvelocity                =300;
		   
		sim_message_simulation_start_resume_request          =4096;
		sim_message_simulation_pause_request                 =4097;
		sim_message_simulation_stop_request                  =4098;

		% Scene object properties 
		sim_objectproperty_collapsed				=16;
		sim_objectproperty_selectable				=32;
		sim_objectproperty_reserved7				=64;
		sim_objectproperty_selectmodelbaseinstead	=128;
		sim_objectproperty_dontshowasinsidemodel	=256;
		


		% type of arguments (input and output) for custom lua commands 
		sim_lua_arg_nil     =0;
		sim_lua_arg_bool	=1;	
		sim_lua_arg_int     =2;
		sim_lua_arg_float   =3;
		sim_lua_arg_string  =4;
		sim_lua_arg_invalid =5;
		sim_lua_arg_table   =8;

		% custom user interface properties 
		sim_ui_property_visible						=1;
		sim_ui_property_visibleduringsimulationonly	=2;
		sim_ui_property_moveable					=4;
		sim_ui_property_relativetoleftborder		=8;
		sim_ui_property_relativetotopborder			=16;
		sim_ui_property_fixedwidthfont				=32;
		sim_ui_property_systemblock					=64;
		sim_ui_property_settocenter					=128;
		sim_ui_property_rolledup					=256;
		sim_ui_property_selectassociatedobject		=512;
		sim_ui_property_visiblewhenobjectselected	=1024;


		% button properties 
		sim_buttonproperty_button				=0;
		sim_buttonproperty_label				=1;
		sim_buttonproperty_slider				=2;
		sim_buttonproperty_editbox				=3;
		sim_buttonproperty_staydown				=8;
		sim_buttonproperty_enabled				=16;
		sim_buttonproperty_borderless			=32;
		sim_buttonproperty_horizontallycentered	=64;
		sim_buttonproperty_ignoremouse			=128;
		sim_buttonproperty_isdown				=256;
		sim_buttonproperty_transparent			=512;
		sim_buttonproperty_nobackgroundcolor	=1024;
		sim_buttonproperty_rollupaction			=2048;
		sim_buttonproperty_closeaction			=4096;
		sim_buttonproperty_verticallycentered	=8192;
		sim_buttonproperty_downupevent			=16384;


		% Simulation status 
		sim_simulation_stopped						=0;								
		sim_simulation_paused						=8;								
		sim_simulation_advancing					=16;								
		sim_simulation_advancing_firstafterstop		=16;		
		sim_simulation_advancing_running			=17;		
		sim_simulation_advancing_lastbeforepause	=19;		
		sim_simulation_advancing_firstafterpause	=20;		
		sim_simulation_advancing_abouttostop		=21;		
		sim_simulation_advancing_lastbeforestop		=22;		


		% Script execution result (first return value) 
		sim_script_no_error					=0;
		sim_script_main_script_nonexistent	=1;
		sim_script_main_script_not_called	=2;
		sim_script_reentrance_error			=4;
		sim_script_lua_error				=8;
		sim_script_call_error				=16;


 		% Script types 
		sim_scripttype_mainscript   =0;
		sim_scripttype_childscript  =1;
		sim_scripttype_pluginscript =2;
		sim_scripttype_threaded     =240;			

		% API call error messages 
		sim_api_errormessage_ignore	=0;	
		sim_api_errormessage_report	=1;	
		sim_api_errormessage_output	=2;  


		% special argument of some functions 
		sim_handle_all						=-2;
		sim_handle_all_except_explicit		=-3;
		sim_handle_self						=-4;
		sim_handle_main_script				=-5;
		sim_handle_tree						=-6;
		sim_handle_chain					=-7;
		sim_handle_single					=-8;
		sim_handle_default					=-9;
		sim_handle_all_except_self			=-10;
		sim_handle_parent					=-11;


		% distance calculation methods 
		sim_distcalcmethod_dl               =0;
		sim_distcalcmethod_dac              =1;
		sim_distcalcmethod_max_dl_dac       =2;
		sim_distcalcmethod_dl_and_dac       =3;
		sim_distcalcmethod_sqrt_dl2_and_dac2=4;
		sim_distcalcmethod_dl_if_nonzero    =5;
		sim_distcalcmethod_dac_if_nonzero   =6;


 		% Generic dialog styles 
		sim_dlgstyle_message		=0;
		sim_dlgstyle_input          =1;
		sim_dlgstyle_ok             =2;
		sim_dlgstyle_ok_cancel      =3;
		sim_dlgstyle_yes_no         =4;
		sim_dlgstyle_dont_center	=32;

 		% Generic dialog return values 
		sim_dlgret_still_open   =0;
		sim_dlgret_ok           =1;
		sim_dlgret_cancel       =2;
		sim_dlgret_yes          =3;
		sim_dlgret_no           =4;


		% Path properties 
		sim_pathproperty_show_line				            =1;
		sim_pathproperty_show_orientation		            =2;
		sim_pathproperty_closed_path			            =4;
		sim_pathproperty_automatic_orientation	            =8;
		sim_pathproperty_invert_velocity		            =16;
		sim_pathproperty_infinite_acceleration	            =32;
		sim_pathproperty_flat_path				            =64;
		sim_pathproperty_show_position			            =128;
		sim_pathproperty_auto_velocity_profile_translation	=256;
		sim_pathproperty_auto_velocity_profile_rotation		=512;
		sim_pathproperty_endpoints_at_zero					=1024;
		sim_pathproperty_keep_x_up							=2048;


 		% drawing objects 
		sim_drawing_points          =0;		
		sim_drawing_lines			=1;       	
		sim_drawing_triangles		=2;	        
		sim_drawing_trianglepoints	=3;	        
		sim_drawing_quadpoints		=4;	        
		sim_drawing_discpoints		=5;	        
		sim_drawing_cubepoints		=6;     	
		sim_drawing_spherepoints	=7;  		

		sim_drawing_itemcolors				=32; 
		sim_drawing_vertexcolors			=64; 
		sim_drawing_itemsizes				=128; 
		sim_drawing_backfaceculling			=256; 
		sim_drawing_wireframe				=512; 
		sim_drawing_painttag				=1024; 
		sim_drawing_followparentvisibility	=2048; 
		sim_drawing_cyclic					=4096; 
		sim_drawing_50percenttransparency	=8192; 
		sim_drawing_25percenttransparency	=16384; 
		sim_drawing_12percenttransparency	=32768; 
		sim_drawing_emissioncolor			=65536; 
		sim_drawing_facingcamera			=131072; 
		sim_drawing_overlay					=262144; 
		sim_drawing_itemtransparency		=524288;  

		% banner values 
		sim_banner_left						=1; 
		sim_banner_right					=2; 
		sim_banner_nobackground				=4; 
		sim_banner_overlay					=8; 
		sim_banner_followparentvisibility	=16; 
		sim_banner_clickselectsparent		=32; 
		sim_banner_clicktriggersevent		=64; 
		sim_banner_facingcamera				=128; 
		sim_banner_fullyfacingcamera		=256; 
		sim_banner_backfaceculling			=512; 
		sim_banner_keepsamesize				=1024; 
		sim_banner_bitmapfont				=2048; 

		% particle objects 
		sim_particle_points1        =0;  
		sim_particle_points2		=1;	
		sim_particle_points4		=2;	
		sim_particle_roughspheres	=3;	
		sim_particle_spheres		=4;	

		sim_particle_respondable1to4		=32; 
		sim_particle_respondable5to8		=64; 
		sim_particle_particlerespondable	=128; 
		sim_particle_ignoresgravity			=256; 
		sim_particle_invisible				=512; 
		sim_particle_itemsizes				=1024; 
		sim_particle_itemdensities			=2048; 
		sim_particle_itemcolors				=4096; 
		sim_particle_cyclic					=8192; 
		sim_particle_emissioncolor			=16384; 
		sim_particle_water					=32768; 
		sim_particle_painttag				=65536; 

		% custom user interface menu attributes 
		sim_ui_menu_title		=1;
		sim_ui_menu_minimize	=2;
		sim_ui_menu_close		=4;
		sim_ui_menu_systemblock =8;



		% Boolean parameters 
		sim_boolparam_hierarchy_visible                 =0;
		sim_boolparam_console_visible                   =1;
		sim_boolparam_collision_handling_enabled        =2;
		sim_boolparam_distance_handling_enabled         =3;
		sim_boolparam_ik_handling_enabled               =4;
		sim_boolparam_gcs_handling_enabled              =5;
		sim_boolparam_dynamics_handling_enabled         =6;
		sim_boolparam_joint_motion_handling_enabled     =7;
		sim_boolparam_path_motion_handling_enabled      =8;
		sim_boolparam_proximity_sensor_handling_enabled =9;
		sim_boolparam_vision_sensor_handling_enabled    =10;
		sim_boolparam_mill_handling_enabled             =11;
		sim_boolparam_browser_visible                   =12;
		sim_boolparam_scene_and_model_load_messages     =13;
		sim_reserved0                                   =14;
		sim_boolparam_shape_textures_are_visible        =15;
		sim_boolparam_display_enabled                   =16;
		sim_boolparam_infotext_visible                  =17;
		sim_boolparam_statustext_open                   =18;
		sim_boolparam_fog_enabled                       =19;
		sim_boolparam_rml2_available                    =20;
		sim_boolparam_rml4_available                    =21;
		sim_boolparam_mirrors_enabled					=22;
		sim_boolparam_aux_clip_planes_enabled			=23;
		sim_boolparam_full_model_copy_from_api			=24;
		sim_boolparam_realtime_simulation				=25;


		% Integer parameters 
		sim_intparam_error_report_mode      =0;  
		sim_intparam_program_version        =1;  
		sim_intparam_instance_count         =2;  
		sim_intparam_custom_cmd_start_id    =3;  
		sim_intparam_compilation_version    =4;  
		sim_intparam_current_page           =5;
		sim_intparam_flymode_camera_handle  =6;  
		sim_intparam_dynamic_step_divider   =7;  
		sim_intparam_dynamic_engine         =8;  
		sim_intparam_server_port_start      =9;  
		sim_intparam_server_port_range      =10; 
		sim_intparam_visible_layers         =11;
		sim_intparam_infotext_style         =12;
		sim_intparam_settings               =13;
		sim_intparam_edit_mode_type         =14;
		sim_intparam_server_port_next       =15; 
		sim_intparam_qt_version             =16; 
		sim_intparam_event_flags_read       =17; 
		sim_intparam_event_flags_read_clear =18; 
		sim_intparam_platform               =19; 
		sim_intparam_scene_unique_id        =20; 

		% Float parameters 
		sim_floatparam_rand=0;
		sim_floatparam_simulation_time_step=1; 

		% String parameters 
		sim_stringparam_application_path=0; 

		% Array parameters 
		sim_arrayparam_gravity          =0;
		sim_arrayparam_fog              =1;
		sim_arrayparam_fog_color        =2;
		sim_arrayparam_background_color1=3;
		sim_arrayparam_background_color2=4;
		sim_arrayparam_ambient_light    =5;

		% User interface elements 
		sim_gui_menubar						=1;
		sim_gui_popups						=2;
		sim_gui_toolbar1					=4;
		sim_gui_toolbar2					=8;
		sim_gui_hierarchy					=16;
		sim_gui_infobar						=32;
		sim_gui_statusbar					=64;
		sim_gui_scripteditor				=128;
		sim_gui_scriptsimulationparameters	=256;
		sim_gui_dialogs						=512;
		sim_gui_browser						=1024;
		sim_gui_all							=65535;


		% Joint modes 
		sim_jointmode_passive       =0;
		sim_jointmode_motion        =1;
		sim_jointmode_ik            =2;
		sim_jointmode_ikdependent   =3;
		sim_jointmode_dependent     =4;
		sim_jointmode_force         =5;


		% Navigation and selection modes with the mouse.
		sim_navigation_passive					=0;
		sim_navigation_camerashift				=1;
		sim_navigation_camerarotate				=2;
		sim_navigation_camerazoom				=3;
		sim_navigation_cameratilt				=4;
		sim_navigation_cameraangle				=5;
		sim_navigation_camerafly				=6;
		sim_navigation_objectshift				=7;
		sim_navigation_objectrotate				=8;
		sim_navigation_reserved2				=9;
		sim_navigation_reserved3				=10;
		sim_navigation_jointpathtest			=11;
		sim_navigation_ikmanip					=12;
		sim_navigation_objectmultipleselection	=13;
		
		sim_navigation_reserved4				=256;
		sim_navigation_clickselection			=512;
		sim_navigation_ctrlselection			=1024;
		sim_navigation_shiftselection			=2048;
		sim_navigation_camerazoomwheel			=4096;
		sim_navigation_camerarotaterightbutton	=8192;


		% Remote API message header structure 
		simx_headeroffset_crc           =0;	
		simx_headeroffset_version       =2;	
		simx_headeroffset_message_id    =3;	
		simx_headeroffset_client_time   =7;	
		simx_headeroffset_server_time   =11;	
		simx_headeroffset_scene_id      =15;
		simx_headeroffset_server_state  =17;	

		% Remote API command header 
		simx_cmdheaderoffset_mem_size       =0;	
		simx_cmdheaderoffset_full_mem_size  =4;	
		simx_cmdheaderoffset_pdata_offset0  =8;	
		simx_cmdheaderoffset_pdata_offset1  =10;	
		simx_cmdheaderoffset_cmd			=14;
		simx_cmdheaderoffset_delay_or_split =18;	
		simx_cmdheaderoffset_sim_time       =20;	
		simx_cmdheaderoffset_status         =24;	
		simx_cmdheaderoffset_reserved       =25;	


		% Regular operation modes 
		simx_opmode_oneshot				=0; 
		simx_opmode_oneshot_wait		=65536; 
		simx_opmode_continuous			=131072;  
		simx_opmode_streaming			=131072; 

		% Operation modes for heavy data 
		simx_opmode_oneshot_split		=196608;   
		simx_opmode_continuous_split	=262144;
		simx_opmode_streaming_split		=262144;	

		% Special operation modes 
		simx_opmode_discontinue			=327680;	
		simx_opmode_buffer				=393216;	
		simx_opmode_remove				=458752;	


		% Command error codes 
		simx_error_noerror					=0;
		simx_error_novalue_flag				=1;		
		simx_error_timeout_flag				=2;		
		simx_error_illegal_opmode_flag		=4;		
		simx_error_remote_error_flag		=8;		
		simx_error_split_progress_flag		=16;		
		simx_error_local_error_flag			=32;		
		simx_error_initialize_error_flag	=64;		
        
    end
    methods
    
        %constructor
        
        function obj = remApi(libname,hfile)
            obj.libName = libname;
            obj.hFile = hfile;
            loadlibrary(obj.libName,obj.hFile);
        end
        
        %destructor
        
        function delete(obj)
            unloadlibrary(obj.libName);
        end


        %api methods

		function [rtn] = simxStart(obj,server,port,waitUntilConnected,doNotReconnectOnceDisconnected,timeOutInMs)
			server_intval = int8([server,0]);
			server_ptr = libpointer('int8Ptr',server_intval);
			if(waitUntilConnected)
				waitUntilConnected_ = int8(49);
			else
				waitUntilConnected_ = int8(48);
			end
			if(doNotReconnectOnceDisconnected)
				doNotReconnectOnceDisconnected_ = int8(49);
			else
				doNotReconnectOnceDisconnected_ = int8(48);
			end
		    
			rtn = calllib(obj.libName,'simxStart',server_ptr,port,waitUntilConnected_,doNotReconnectOnceDisconnected_,timeOutInMs);
		end

		function simxFinish(obj)
			calllib(obj.libName,'simxFinish');
		end

		function rtn = simxAddStatusbarMessage(obj,message,operationmode)
			message_ = libpointer('int8Ptr',[int8(message) 0]);
			operationmode_ = int32(operationmode);

			[rtn message_] = calllib(obj.libName,'simxAddStatusbarMessage',message_,operationmode_);
		end		
		        
		function rtn = simxAuxiliaryConsoleClose(obj,console, operationmode)
			console_ = int32(console);
			operationmode_ = int32(operationmode);
		    
			rtn = calllib(obj.libName,'simxAuxiliaryConsoleClose',console_,operationmode_)
		end    
    
		function [rtn console_handle] = simxAuxiliaryConsoleOpen(obj,title,maxLines,mode,position,size,textcolor,backgroundcolor,operationmode)
			title_ = libpointer('int8Ptr',[int8(title) 0]);
			maxLines_ = int32(maxLines);
			mode_ = int32(mode);

			if (numel(position) < 2)&&(numel(position) ~= 0)
				error('position should have 2 values');
				return;
			end
			if (numel(size) < 2)&&(numel(size) ~= 0)
				error('size should have 2 values');
				return;
			end
			if (numel(textcolor) < 3)&&(numel(textcolor) ~= 0)
				error('textcolor should have 3 values');
				return;
			end
			if (numel(backgroundcolor) < 3)&&(numel(backgroundcolor) ~= 0)
				error('backgroundcolor should have 3 values');
				return;
			end
			
			position_ = libpointer('int32Ptr',int32(position));
			size_ = libpointer('int32Ptr',int32(size));
			textcolor_ = libpointer('singlePtr',single(textcolor));
			backgroundcolor_ = libpointer('singlePtr',single(backgroundcolor));
			consolehandle_ = libpointer('int32Ptr',int32(0));
			operationmode_ = int32(operationmode);
		    
			[rtn a b c d e console_handle] = calllib(obj.libName,'simxAuxiliaryConsoleOpen',title_,maxLines_,mode_,position_,size_,textcolor_,backgroundcolor_,consolehandle_,operationmode);
		end
    
		function rtn = simxAuxiliaryConsolePrint(obj,console,text,operationmode)
			console_ = int32(console);
			operationmode_ = int32(operationmode);
		    
			if text
				text_ = libpointer('int8Ptr',[int8(text) 0]);
			else
				text_ = [];
			end

			rtn = calllib(obj.libName,'simxAuxiliaryConsolePrint',console_,text_,operationmode_);
		end    
    
		 function rtn = simxAuxiliaryConsoleShow(obj,consoleHandle,showState,operationMode)
			consoleHandle_ = int32(consoleHandle);
			showState_ = int8(showState);
			operationMode_ = int32(operationMode);

			rtn = calllib(obj.libName,'simxAuxiliaryConsoleShow',consoleHandle_,showState_,operationMode_);
		end   
    
		function rtn = simxBreakForceSensor(obj,forceSensorHandle,operationMode)
			forceSensorHandle_ = int32(forceSensorHandle);
			operationMode_ = int32(operationMode);

			rtn = calllib(obj.libName, 'simxBreakForceSensor',forceSensorHandle_,operationMode_);
		end    

		function rtn = simxClearFloatSignal(obj,signalName,operationMode)
			signalName_ = libpointer('int8Ptr',[int8(signalName) 0]);
			operationMode_ = int32(operationMode);
		    
			rtn = calllib(obj.libName,'simxClearFloatSignal',signalName_,operationMode_);
		end    

		function rtn = simxClearIntegerSignal(obj,signalName,operationMode)
			signalName_ = libpointer('int8Ptr',[int8(signalName) 0]);
			operationMode_ = int32(operationMode);
		    
			rtn = calllib(obj.libName,'simxClearIntegerSignal',signalName_,operationMode_);
		end

		function rtn = simxClearStringSignal(obj,signalName,operationMode)
			signalName_ = libpointer('int8Ptr',[int8(signalName) 0]);
			operationMode_ = int32(operationMode);
		    
			rtn = calllib(obj.libName,'simxClearStringSignal',signalName_,operationMode_);
		end

		function rtn = simxCloseScene(obj,operationMode)
			operationMode_ = int32(operationMode);
		    
			rtn = calllib(obj.libName,'simxCloseScene',operationMode_);
		end

		function [rtn newObjectHandles] = simxCopyPasteObjects(obj,objectHandles,operationMode)
			objectHandles_ = libpointer('int32Ptr',int32(objectHandles));
			objectCount_ = int32(numel(objectHandles));
			newObjectHandles_ = libpointer('int32Ptr',[]);
			newObjectCount_ = libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);
		    
			[rtn objectHandles_ newObjectHandles_ newObjectCount_] = calllib(obj.libName,'simxCopyPasteObjects',objectHandles_,objectCount_,newObjectHandles_,newObjectCount_,operationMode_);

			if (rtn==0)&&(newObjectCount_>0) 
				newObjectHandles = zeros(1,newObjectCount_);
				newObjectHandles_.setdatatype('int32Ptr',1,newObjectCount_);
				for i=1:newObjectCount_;
					newObjectHandles(i) = newObjectHandles_.value(i);
				end
			else
				newObjectHandles=[];
			end
		end

		function buffer = simxCreateBuffer(obj,bufferSize)
			bufferSize_ = int32(bufferSize);

			buffer = calllib(obj.libName,'simxCreateBuffer',bufferSize_);
		end
    
		function [rtn dialogHandle uiHandle] = simxDisplayDialog(obj,titleText,mainText,dialogType,initialText,titleColors,dialogColors,operationMode)
			if (numel(titleColors) < 6)&&(numel(titleColors) ~= 0)
				error('titleColors should have 6 values');
				return;
			end
			if (numel(dialogColors) < 6)&&(numel(dialogColors) ~= 0)
				error('dialogColors should have 6 values');
				return;
			end
		    
			titleText_ = libpointer('int8Ptr',[int8(titleText) 0]);
			mainText_ = libpointer('int8Ptr',[int8(mainText) 0]);
			dialogType_ = int32(dialogType);
			initialText_ = libpointer('int8Ptr',[int8(initialText) 0]);
			titleColors_ = libpointer('singlePtr', single(titleColors));
			dialogColors_ = libpointer('singlePtr', single(dialogColors));
			operationMode_ = int32(operationMode);
			dialogHandle = libpointer('int32Ptr',int32(0));
			uiHandle = libpointer('int32Ptr',int32(0));
		        
			[rtn a b c d e dialogHandle uiHandle] = calllib(obj.libName,'simxDisplayDialog',titleText_,mainText_,dialogType_,initialText_,titleColors_,dialogColors_,dialogHandle,uiHandle,operationMode_);
		end    
    
		function rtn = simxEndDialog(obj,dialogHandle,operationMode)
			operationMode_ = int32(operationMode);
			dialogHandle_ = int32(dialogHandle);

			rtn = calllib(obj.libName,'simxEndDialog',dialogHandle_,operationMode_);
		end    
 
		function rtn = simxEraseFile(obj,fileName_serverSide,operationMode)
			fileName_serverSide_ = libpointer('int8Ptr',[int8(fileName_serverSide) 0]);
			operationMode_ = int32(operationMode);
		    
			[rtn fileName_serverSide_] = calllib(obj.libName,'simxEraseFile',fileName_serverSide_,operationMode_);
		end 
 
		function [rtn paramValues ]= simxGetArrayParameter(obj,paramIdentifier,operationMode)
			paramIdentifier_ = int32(paramIdentifier);
			operationMode_ = int32(operationMode);
			paramValues = libpointer('singlePtr',single([0 0 0]));

			[rtn paramValues] = calllib(obj.libName,'simxGetArrayParameter',paramIdentifier_,paramValues ,operationMode_);
		end 
 
		function [rtn paramValues ]= simxGetBooleanParameter(obj,paramIdentifier,operationMode)
			paramIdentifier_ = int32(paramIdentifier);
			operationMode_ = int32(operationMode);
			paramValues = libpointer('int8Ptr',int8(0));

			[rtn paramValues] = calllib(obj.libName,'simxGetBooleanParameter',paramIdentifier_,paramValues ,operationMode_);
		end 
 
		function [rtn handle] = simxGetCollisionHandle(obj,collisionObjectName,operationMode)
			collisionObjectName_ = libpointer('int8Ptr',[int8(collisionObjectName) 0]);
			handle_ = libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);

			[rtn collisionObjectName_ handle] = calllib(obj.libName,'simxGetCollisionHandle',collisionObjectName_,handle_ ,operationMode_);
		end 
 
		function rtn = simxGetConnectionId(obj)
			rtn = calllib(obj.libName,'simxGetConnectionId');
		end 
 
		 function [rtn inputText]= simxGetDialogInput(obj,dialogHandle,operationMode)
			dialogHandle_ = int32(dialogHandle);
			inputText_ = libpointer('int8PtrPtr');
			operationMode_ = int32(operationMode);

			[rtn inputText_ ] = calllib(obj.libName,'simxGetDialogInput',dialogHandle_,inputText_,operationMode_);

			if (rtn==0) 
				s=1;
				inputText_.setdatatype('int8Ptr',1,s);
				value = inputText_.value(s);
				while(value ~= 0)
					inputText_.setdatatype('int8Ptr',1,s);
					value = inputText_.value(s);
					s=s+1;
				end
				tmp = inputText_.value(1:s-1);
				inputText = char(tmp);
			else
				inputText = [];
			end
		end
 
		function [rtn result]= simxGetDialogResult (obj,dialogHandle,operationMode)
			dialogHandle_  = int32(dialogHandle);
			result = libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);

			[rtn result] = calllib(obj.libName,'simxGetDialogResult',dialogHandle_,result,operationMode_);
		end 
 
		function [rtn handle] = simxGetDistanceHandle(obj,distanceObjectName,operationMode)
			distanceObjectName_ = libpointer('int8Ptr',[int8(distanceObjectName) 0]);
			handle_ = libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);

			[rtn distanceObjectName_ handle] = calllib(obj.libName,'simxGetDistanceHandle',distanceObjectName_,handle_ ,operationMode_);
		end 
 
		function [rtn paramValue]= simxGetFloatingParameter(obj,paramIdentifier,operationMode)
			paramIdentifier_ = int32(paramIdentifier);
			operationMode_ = int32(operationMode);
			paramValue = libpointer('singlePtr',single(0));

			[rtn paramValue] = calllib(obj.libName,'simxGetFloatingParameter',paramIdentifier_,paramValue,operationMode_);
		end 
 
		function [rtn signalValue]= simxGetFloatSignal(obj,signalName,operationMode)
			signalName_ = libpointer('int8Ptr',[int8(signalName) 0]);
			signalValue = libpointer('singlePtr',single(0));
			operationMode_ = int32(operationMode);

			[rtn signalName_ signalValue] = calllib(obj.libName,'simxGetFloatSignal',signalName_,signalValue,operationMode_);
		end 
 
		function [rtn info]= simxGetInMessageInfo(obj,infoType)
			infoType_ = int32(infoType);
			info = libpointer('int32Ptr',int32(0));

			[rtn info] = calllib(obj.libName,'simxGetInMessageInfo',infoType_,info);
		end 
 
		function [rtn paramValue]= simxGetIntegerParameter (obj,paramIdentifier,operationMode)
			paramIdentifier_ = int32(paramIdentifier);
			operationMode_ = int32(operationMode);
			paramValue = libpointer('int32Ptr',int32(0));

			[rtn paramValue] = calllib(obj.libName,'simxGetIntegerParameter',paramIdentifier_,paramValue,operationMode_);
		end 
 
		function [rtn signalValue]= simxGetIntegerSignal(obj,signalName,operationMode)
			signalName_ = libpointer('int8Ptr',[int8(signalName) 0]);
			signalValue = libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);
		    
			[rtn signalName signalValue] = calllib(obj.libName,'simxGetIntegerSignal',signalName_,signalValue,operationMode_);
		end 
 
		function [rtn matrix] = simxGetJointMatrix(obj,jointHandle,operationMode)
			jointHandle_ = int32(jointHandle);
			matrix = libpointer('singlePtr',single([0 0 0 0 0 0 0 0 0 0 0 0]));
			operationMode_ = int32(operationMode);
		    
		   [rtn matrix ] = calllib(obj.libName,'simxGetJointMatrix',jointHandle_,matrix, operationMode_);
		end 
 
		function [rtn position] = simxGetJointPosition(obj,handle,option)
			handle_ = int32(handle);
			option_ = int32(option);
		   
			[rtn position] = calllib(obj.libName,'simxGetJointPosition',handle_,single(43),option_);
		end    

		function rtn = simxGetLastCmdTime(obj)
			rtn = calllib(obj.libName,'simxGetLastCmdTime');
		end

		function [rtn errorStrings]= simxGetLastErrors(obj,operationMode)
			errorCnt = libpointer('int32Ptr',int32(0));
			errorStrings_ = libpointer('int8PtrPtr');
			operationMode_ = int32(operationMode);

			[rtn errorCnt errorStrings_ ] = calllib(obj.libName,'simxGetLastErrors',errorCnt,errorStrings_,operationMode_);

			if (rtn==0) 
				errorStrings = cell(double(errorCnt));
				s=1;
				for i=1:errorCnt
					begin = s;
					errorStrings_.setdatatype('int8Ptr',1,s);
					value = errorStrings_.value(s);
					while(value ~= 0)
						errorStrings_.setdatatype('int8Ptr',1,s);
						value = errorStrings_.value(s);
						s=s+1;
					end
					tmp = errorStrings_.value(begin:s-1);
					errorStrings(i) = cellstr(char(tmp));
				end
			else
				errorStrings=[];
			end
		end

		function [rtn prop] = simxGetModelProperty(obj,objectHandle,operationMode)
			objectHandle_ = int32(objectHandle);
			operationMode_ = int32(operationMode);
			prop = libpointer('int32Ptr',int32(0));
		    
			[rtn prop ] = calllib(obj.libName,'simxGetModelProperty',objectHandle_,prop,operationMode_);
		end

		function [rtn childObjectHandle] = simxGetObjectChild(obj,parentObjectHandle,childIndex,operationMode)
			parentObjectHandle_ = int32(parentObjectHandle);
			childIndex_ = int32(childIndex);
			childObjectHandle = libpointer('int32Ptr',int32(0));    
			operationMode_ = int32(operationMode);

			[rtn childObjectHandle ] = calllib(obj.libName,'simxGetObjectChild',parentObjectHandle_,childIndex_,childObjectHandle,operationMode_);
		end

		function [rtn paramValue]= simxGetObjectFloatParameter(obj,objectHandle,parameterID,operationMode)
			objectHandle_ = int32(objectHandle);
			parameterID_ = int32(parameterID);
			operationMode_ = int32(operationMode);
			paramValue = libpointer('singlePtr',single(0));

			[rtn paramValue] = calllib(obj.libName,'simxGetObjectFloatParameter',objectHandle_,parameterID_,paramValue,operationMode_);
		end

		function [rtn handle] = simxGetObjectHandle(obj,name,operationmode)
			name_ptr = libpointer('int8Ptr',[int8(name) 0]);
			handle_ptr = libpointer('int32Ptr',int32(0));
			operationmode_ = int32(operationmode);
		    
			[rtn name_ptr handle] = calllib(obj.libName,'simxGetObjectHandle',name_ptr,handle_ptr,operationmode_);
		end

		function [rtn paramValue]= simxGetObjectIntParameter(obj,objectHandle,parameterID,operationMode)
			objectHandle_ = int32(objectHandle);
			parameterID_ = int32(parameterID);
			operationMode_ = int32(operationMode);
			paramValue = libpointer('int32Ptr',int32(0));

			[rtn paramValue] = calllib(obj.libName,'simxGetObjectIntParameter',objectHandle_,parameterID_,paramValue,operationMode_);
		end

		function [rtn eulerAngles] = simxGetObjectOrientation(obj,objectHandle,relativeToObjectHandle,operationMode)
			objectHandle_ = int32(objectHandle);
			relativeToObjectHandle_ = int32(relativeToObjectHandle);
			operationMode_ = int32(operationMode);
			eulerAngles = libpointer('singlePtr', single([0 0 0]));
		    
			[rtn eulerAngles] = calllib(obj.libName,'simxGetObjectOrientation',objectHandle_,relativeToObjectHandle_,eulerAngles ,operationMode_);
		end

		function [rtn parentObjectHandle] = simxGetObjectParent(obj,objectHandle,operationMode)
			objectHandle_ = int32(objectHandle);
			parentObjectHandle = libpointer('int32Ptr',int32(0));    
			operationMode_ = int32(operationMode);

			[rtn parentObjectHandle] = calllib(obj.libName,'simxGetObjectParent',objectHandle_,parentObjectHandle,operationMode);
		end

		function [rtn position] = simxGetObjectPosition(obj,objectHandle,relativeToObjectHandle,operationMode)
			objectHandle_ = int32(objectHandle);
			relativeToObjectHandle_ = int32(relativeToObjectHandle);
			operationMode_ = int32(operationMode);
			position = libpointer('singlePtr', single([0 0 0]));
		    
			[rtn position] = calllib(obj.libName,'simxGetObjectPosition',objectHandle_,relativeToObjectHandle_,position ,operationMode_);
		end

		function [rtn objectHandles] = simxGetObjects(obj,objectType,operationMode)
			objectType_ = int32(objectType);
			objectHandles_ = libpointer('int32PtrPtr');
			objectCount = libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);

			[rtn objectCount objectHandles_]  = calllib(obj.libName,'simxGetObjects',objectType_,objectCount,objectHandles_,operationMode_);
			
			if (rtn==0)
				if(objectCount > 0 )  
					objectHandles_.setdatatype('int32Ptr',1,objectCount);
					objectHandles = objectHandles_.value;
				else
					objectHandles = [];
				end
			else
				objectHandles = [];
			end
		end

		function [rtn objectHandles ] = simxGetObjectSelection(obj,operationMode)
			objectHandles_ = libpointer('int32PtrPtr');
			objectCount = libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);

			[rtn objectHandles_ objectCount] = calllib(obj.libName,'simxGetObjectSelection',objectHandles_ ,objectCount,operationMode_);
			
			if (rtn==0)	
				if(objectCount > 0)
					objectHandles_.setdatatype('int32Ptr',1,objectCount);
					objectHandles = objectHandles_.value;
				else
					objectHandles = [];
				end
			else
				objectHandles = [];
			end
		end

		function [rtn info]= simxGetOutMessageInfo(obj,infoType)
			infoType_ = int32(infoType);
			info = libpointer('int32Ptr',int32(0));
		    
			[rtn info] = calllib(obj.libName,'simxGetOutMessageInfo',infoType_,info);
		end
		
		function [rtn pingTime]= simxGetPingTime(obj)
			pingTime = libpointer('int32Ptr',int32(0));
		    
			[rtn pingTime] = calllib(obj.libName,'simxGetPingTime',pingTime);
		end

		function [rtn paramValue]= simxGetStringParameter(obj,paramIdentifier,operationMode)
			paramIdentifier_ = int32(paramIdentifier);
			operationMode_ = int32(operationMode);
			paramValue_ = libpointer('int8PtrPtr');

			[rtn paramValue_] = calllib(obj.libName,'simxGetStringParameter',paramIdentifier_,paramValue_,operationMode_);

			if(rtn == 0)
				s=1;
				paramValue_.setdatatype('int8Ptr',1,s);
				value = paramValue_.value(s);
				while(value ~= 0)
					paramValue_.setdatatype('int8Ptr',1,s);
					value = paramValue_.value(s);
					s=s+1;
				end
				tmp = paramValue_.value(1:s-1);
				paramValue = char(tmp);
			else
				paramValue = [];
			end
		end

		function [rtn signalValue ]= simxGetStringSignal(obj,signalName,operationMode)
			signalName_ = libpointer('int8Ptr',[int8(signalName) 0]);
			signalValue_ = libpointer('int8PtrPtr');
			signalLength= libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);

			[rtn signalName_ signalValue_ signalLength ] = calllib(obj.libName,'simxGetStringSignal',signalName_,signalValue_,signalLength ,operationMode_);

			if (rtn==0)
				signalValue_.setdatatype('int8Ptr',1,double(signalLength));
				signalValue = char(signalValue_.value);
			else
				signalValue = [];
			end
		end

		function [rtn prop] = simxGetUIButtonProperty(obj,uiHandle,uiButtonID,operationMode)
   			uiHandle_ = int32(uiHandle);
			operationMode_ = int32(operationMode);
			uiButtonID_ = int32(uiButtonID);
			prop = libpointer('int32Ptr',int32(0));
		    
			[rtn prop ] = calllib(obj.libName,'simxGetUIButtonProperty',uiHandle_,uiButtonID_,prop,operationMode_);
		end

		function [rtn uiEventButtonID auxValues] = simxGetUIEventButton(obj,uiHandle,operationMode)
			uiHandle_ = int32(uiHandle);
			operationMode_ = int32(operationMode);
			uiEventButtonID = libpointer('int32Ptr',int32(0));
			auxValues = libpointer('int32Ptr',int32([0 0]));

			[rtn uiEventButtonID auxValues] = calllib(obj.libName,'simxGetUIEventButton',uiHandle_,uiEventButtonID ,auxValues ,operationMode_);
		end

		function [rtn handle] = simxGetUIHandle(obj,uiName,operationMode)
   			uiName_ = libpointer('int8Ptr',[int8(uiName) 0]);
			operationMode_ = int32(operationMode);
			handle = libpointer('int32Ptr',int32(0));
		    
			[rtn uiName handle] = calllib(obj.libName,'simxGetUIHandle',uiName_,handle,operationMode_);
		end

		function [rtn position] = simxGetUISlider(obj,uiHandle,uiButtonID,operationMode)
   			uiHandle_ = int32(uiHandle);
			operationMode_ = int32(operationMode);
			uiButtonID_ = int32(uiButtonID);
			position = libpointer('int32Ptr',int32(0));
		    
   			[rtn position ] = calllib(obj.libName,'simxGetUISlider',uiHandle_,uiButtonID_,position,operationMode_)
		end

		function [rtn resolution_ buffer] = simxGetVisionSensorDepthBuffer(obj,handle,operationmode)
			resolution = [0 0];
			resolution_ = libpointer('int32Ptr',int32(resolution));
			buffer = libpointer('singlePtr',[]);
			operationmode_ = int32(operationmode);
			handle_ = int32(handle);

			[rtn resolution_ buffer] = calllib(obj.libName,'simxGetVisionSensorDepthBuffer',handle_,resolution_,buffer,operationmode_);
		end

		function [rtn resolution_ buffer] = simxGetVisionSensorDepthBuffer2(obj,handle,operationmode)
			resolution = [0 0];
			resolution_ = libpointer('int32Ptr',int32(resolution));
			buffer_ = libpointer('singlePtr',[]);
			operationmode_ = int32(operationmode);
			handle_ = int32(handle);

			[rtn resolution_ buffer_] = calllib(obj.libName,'simxGetVisionSensorDepthBuffer',handle_,resolution_,buffer_,operationmode_);

			if (rtn==0)
				if((resolution_(1) ~= 0) && (resolution_(2) ~= 0))
					buffer_.setdatatype('singlePtr',1,resolution_(1)*resolution_(2));
					buffer = zeros(resolution_(1),resolution_(2));
					buffer = cast(buffer,'single');
					for i = resolution_(1):-1:1;
						count = (resolution_(1)-i)*resolution_(2);
						for j = 1:resolution_(2);
							buffer(i,j) = single(buffer_.value(count+j));
						end
					end
				end
			else
				buffer = [];
			end
		end

		function [rtn resolution_ image] = simxGetVisionSensorImage(obj,handle,options,operationmode)
			resolution = [0 0];
			resolution_ = libpointer('int32Ptr',int32(resolution));
			image = libpointer('int8Ptr',[]);
			options_ = int8(options);
			operationmode_ = int32(operationmode);
			handle_ = int32(handle);

			[rtn resolution_ image] = calllib(obj.libName,'simxGetVisionSensorImage',handle_,resolution_,image,options_,operationmode_);
		end

		function [rtn resolution_ image] = simxGetVisionSensorImage2(obj,handle,options,operationmode)
			resolution = [0 0];
			resolution_ = libpointer('int32Ptr',int32(resolution));
			image_ = libpointer('int8Ptr',[]);
			options_ = int8(options);
			operationmode_ = int32(operationmode);
			handle_ = int32(handle);
		 
			[rtn resolution_ image_] = calllib(obj.libName,'simxGetVisionSensorImage',handle_,resolution_,image_,options_,operationmode_);

			if (rtn==0)
				if((resolution_(1) ~= 0) && (resolution_(2) ~= 0))
					if(options == 1) %grayscale image
						image_.setdatatype('uint8Ptr',1,resolution_(1)*resolution_(2));
						image = zeros(resolution_(1),resolution_(2));
						image = cast(image,'uint8');
						for i = resolution_(1):-1:1;
							count = (resolution_(1)-i)*resolution_(2);
							for j = 1:resolution_(2);
								image(i,j) = uint8(image_.value(count+j));
							end
						end
					else 
						image_.setdatatype('uint8Ptr',1,resolution_(1)*resolution_(2)*3);
						image = zeros(resolution_(1),resolution_(2),3);
						image = cast(image,'uint8');
						for i = resolution_(1):-1:1;
							count = (resolution_(1)-i)*resolution_(2)*3;
							for j = 1:3:resolution_(2)*3;
								for k=1:3;
									l=int32(j/3) +1;
									image(i,l,k) = uint8(image_.value(count+j+k-1));  
								end
							end
						end
					end
				end
			else
				image = [];
			end
		end

		function [rtn force]= simxJointGetForce(obj,jointHandle,operationMode)
			jointHandle_ = int32(jointHandle);
			operationMode_ = int32(operationMode);
			force = libpointer('single',single(0));

			[rtn force ] = calllib(obj.libName,'simxJointGetForce',jointHandle_,single(0),operationMode_);
		end

		function [rtn baseHandle]= simxLoadModel(obj,modelPathAndName,options,operationMode)
			modelPathAndName_ = libpointer('int8Ptr',[int8(modelPathAndName) 0]);
			options_ = int8(options);
			baseHandle= libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);
		    
			[rtn modelPathAndName_ baseHandle] = calllib(obj.libName,'simxLoadModel',modelPathAndName_,options_,baseHandle,operationMode_);
		end

		function [rtn ]= simxLoadScene(obj,scenePathAndName,options,operationMode)
			scenePathAndName_ = libpointer('int8Ptr',[int8(scenePathAndName) 0]);
			options_ = int8(options);
			operationMode_ = int32(operationMode);

			[rtn scenePathAndName_ ] = calllib(obj.libName,'simxLoadScene',scenePathAndName_,options_,operationMode_);
		end

		function [rtn uiHandles] = simxLoadUI(obj,uiPathAndName,options,operationMode)
			uiPathAndName_ = libpointer('int8Ptr',int8([uiPathAndName 0]));
			options_ = int8(options);
			count = libpointer('int32Ptr', int32(0));
			uiHandles_ = libpointer('int32Ptr');
			operationMode_ = int32(operationMode);

			[rtn uiPathAndName_ count uiHandles_ ] = calllib(obj.libName,'simxLoadUI',uiPathAndName_,options_,count ,uiHandles_ ,operationMode_);

			if (rtn==0)
				if(count > 0)
					uiHandles_.setdatatype('int32Ptr',1,count);
					uiHandles = uiHandles_.value;
				else
					uiHandles = [];
				end
				uiHandles_.setdatatype('int8Ptr',2,2);
				obj.simxReleaseBuffer(uiHandles_);
			else
				uiHandles = [];
			end
		end
		
		function rtn = simxPauseSimulation(obj,operationMode)
			operationMode_ = int32(operationMode);
		    
			rtn = calllib(obj.libName,'simxPauseSimulation',operationMode_);
		end		
		
		function [rtn collisionState]= simxReadCollision(obj,collisionObjectHandle,operationMode)
			collisionObjectHandle_ = int32(collisionObjectHandle);
			operationMode_ = int32(operationMode);
			collisionState = libpointer('int8Ptr',int8(0));

			[rtn collisionState] = calllib(obj.libName,'simxReadCollision',collisionObjectHandle_,collisionState,operationMode_);
		end		
		
		function [rtn minimumDistance]= simxReadDistance(obj,distanceObjectHandle,operationMode)
			distanceObjectHandle_ = int32(distanceObjectHandle);
			operationMode_ = int32(operationMode);
			minimumDistance = libpointer('singlePtr',single(0));

			[rtn minimumDistance] = calllib(obj.libName,'simxReadDistance',distanceObjectHandle_,minimumDistance,operationMode_);
		end		
		
		function [rtn state forceVector torqueVector]= simxReadForceSensor(obj,forceSensorHandle,operationMode)
			forceSensorHandle_ = int32(forceSensorHandle);
			state = libpointer('int8Ptr', int8(0));
			forceVector = libpointer('singlePtr', single([0 0 0]));
			torqueVector = libpointer('singlePtr', single([0 0 0]));
			operationMode_ = int32(operationMode);

			[rtn state forceVector torqueVector] = calllib(obj.libName,'simxReadForceSensor',forceSensorHandle_,state ,forceVector, torqueVector,operationMode_);
		end		
		
		function [rtn detectionState detectedPoint detectedObjectHandle detectedSurfaceNormalVector]= simxReadProximitySensor(obj,sensorHandle,operationMode)
			sensorHandle_ = int32(sensorHandle);
			detectionState = libpointer('int8Ptr', int8(0));
			detectedPoint = libpointer('singlePtr', single([0 0 0]));
			detectedSurfaceNormalVector = libpointer('singlePtr', single([0 0 0]));
			detectedObjectHandle = libpointer('int32Ptr',int32(0));
			operationMode_ = int32(operationMode);

			[rtn detectionState detectedPoint detectedObjectHandle detectedSurfaceNormalVector] = calllib(obj.libName,'simxReadProximitySensor',sensorHandle_,detectionState ,detectedPoint , detectedObjectHandle ,detectedSurfaceNormalVector,operationMode_);
		end		
		
		function [rtn detectionState auxValues auxValuesCount ] = simxReadVisionSensor(obj,sensorHandle,operationmode)
			detectionState = libpointer('int8Ptr',int8(0));
			auxValues_ = libpointer('singlePtrPtr');
			auxValuesCount_ = libpointer('int32PtrPtr');
			operationmode_ = int32(operationmode);
			sensorHandle_ = int32(sensorHandle);

			[rtn detectionState auxValues_ auxValuesCount_] = calllib(obj.libName,'simxReadVisionSensor',sensorHandle_,detectionState ,auxValues_,auxValuesCount_,operationmode_);

			auxValues = [];
			auxValuesCount = [];
			if(rtn == 0)
				auxValuesCount_.setdatatype('int32Ptr',1,999);
				packets=auxValuesCount_.value(1);
				auxValues_.setdatatype('singlePtr',single(999));
				n=1;
				for i=1:packets
					cnt=auxValuesCount_.value(i+1);
					auxValuesCount=[auxValuesCount cnt];
					for j=1:cnt
						v=auxValues_.value(n);
						n=n+1;
						auxValues=[auxValues v];
					end
				end
				auxValuesCount_.setdatatype('int8Ptr',2,2);
				auxValues_.setdatatype('int8Ptr',2,2);
				obj.simxReleaseBuffer(auxValuesCount_);
				obj.simxReleaseBuffer(auxValues_);
			end
		end		
		
		function [] = simxReleaseBuffer(obj,buffer)
			buffer_ = calllib(obj.libName,'simxReleaseBuffer',buffer);
		end		
		
		function [rtn ] = simxRemoveObject(obj,objectHandle,operationMode)
			objectHandle_ = int32(objectHandle);
			operationMode_ = int32(operationMode);

			[rtn ]  = calllib(obj.libName,'simxRemoveObject',objectHandle_,operationMode_);
		end		
		
		function [rtn ] = simxRemoveUI(obj,uiHandle,operationMode)
			uiHandle_ = int32(uiHandle);
			operationMode_ = int32(operationMode);

			[rtn ]  = calllib(obj.libName,'simxRemoveUI',uiHandle_,operationMode_);
		end		
		
		function [rtn ]= simxSetArrayParameter(obj,paramIdentifier,paramValues,operationMode)
			paramIdentifier_ = int32(paramIdentifier);
			num_ele = numel(paramValues);
			if (num_ele < 3)
				error('paramValues should have 3 values');
			else
				paramValues_ = libpointer('singlePtr',single(paramValues));
				operationMode_ = int32(operationMode);
		        
				[rtn paramValues_ ] = calllib(obj.libName,'simxSetArrayParameter',paramIdentifier_,paramValues_,operationMode_);
			end
		end		
		
		function [rtn ]= simxSetBooleanParameter(obj,paramIdentifier,paramValue,operationMode)
			paramIdentifier_ = int32(paramIdentifier);
			paramValue_ = int8(paramValue);
			operationMode_ = int32(operationMode);
		    
			[rtn ] = calllib(obj.libName,'simxSetBooleanParameter',paramIdentifier_,paramValue_,operationMode_);
		end		
    
		function [rtn ]= simxSetFloatingParameter(obj,paramIdentifier,paramValue,operationMode)
			paramIdentifier_ = int32(paramIdentifier);
			paramValue_ = single(paramValue);
			operationMode_ = int32(operationMode);
		    
			[rtn ] = calllib(obj.libName,'simxSetFloatingParameter',paramIdentifier_,paramValue_,operationMode_);
		end  

		function [rtn ]= simxSetFloatSignal(obj,signalName,signalValue,operationMode)
			signalName_ = libpointer('int8Ptr',[int8(signalName) 0]);
			signalValue_ = single(signalValue);
			operationMode_ = int32(operationMode);

			[rtn signalName_ ] = calllib(obj.libName,'simxSetFloatSignal',signalName_,signalValue_,operationMode_);
		end

		function [rtn ]= simxSetIntegerParameter(obj,paramIdentifier,paramValue,operationMode)
			paramIdentifier_ = int32(paramIdentifier);
			paramValue_ = int32(paramValue);
			operationMode_ = int32(operationMode);
		    
			[rtn ] = calllib(obj.libName,'simxSetIntegerParameter',paramIdentifier_,paramValue_,operationMode_);
		end

		function [rtn ]= simxSetIntegerSignal(obj,signalName,signalValue,operationMode)
			signalName_ = libpointer('int8Ptr',[int8(signalName) 0]);
			signalValue_ = int32(signalValue);
			operationMode_ = int32(operationMode);

			[rtn signalName_ ] = calllib(obj.libName,'simxSetIntegerSignal',signalName_,signalValue_,operationMode_);
		end

		function [rtn ]= simxSetJointForce(obj,objectHandle,targetVelocity,operationMode)
			objectHandle_ = int32(objectHandle);
			targetVelocity_ = single(targetVelocity);
			operationMode_ = int32(operationMode);

			[rtn ] = calllib(obj.libName,'simxSetJointForce',objectHandle_,targetVelocity_,operationMode_);
		end

		function rtn = simxSetJointPosition(obj,handle,position,option)
			handle_ = int32(handle);
			position_ = single(position);
			option_ = int32(option);
			rtn = calllib(obj.libName,'simxSetJointPosition',handle_,position_,option_);
		end

		function [rtn ]= simxSetJointTargetPosition(obj,objectHandle,targetVelocity,operationMode)
			objectHandle_ = int32(objectHandle);
			targetVelocity_ = single(targetVelocity);
			operationMode_ = int32(operationMode);

			[rtn ] = calllib(obj.libName,'simxSetJointTargetPosition',objectHandle_,targetVelocity_,operationMode_);
		end

		function [rtn ]= simxSetJointTargetVelocity(obj,objectHandle,targetVelocity,operationMode)
			objectHandle_ = int32(objectHandle);
			targetVelocity_ = single(targetVelocity);
			operationMode_ = int32(operationMode);

			[rtn ] = calllib(obj.libName,'simxSetJointTargetVelocity',objectHandle_,targetVelocity_,operationMode_);
		end

		function [rtn ]= simxSetModelProperty(obj,objectHandle,prop,operationMode)
			objectHandle_ = int32(objectHandle);
			prop_ = int32(prop);
			operationMode_ = int32(operationMode);

			[rtn ] = calllib(obj.libName,'simxSetModelProperty',objectHandle_,prop_,operationMode_);
		end

		function [rtn ]= simxSetObjectFloatParameter(obj,objectHandle,parameterID,parameterValue,operationMode)
			objectHandle_ = int32(objectHandle);
			parameterID_ = int32(parameterID);
			parameterValue_ = single(parameterValue);
			operationMode_ = int32(operationMode);

			[rtn ] = calllib(obj.libName,'simxSetObjectFloatParameter',objectHandle_,parameterID_,parameterValue_,operationMode_);
		end

		function [rtn ]= simxSetObjectIntParameter(obj,objectHandle,parameterID,parameterValue,operationMode)
			objectHandle_ = int32(objectHandle);
			parameterID_ = int32(parameterID);
			parameterValue_ = int32(parameterValue);
			operationMode_ = int32(operationMode);

			[rtn ] = calllib(obj.libName,'simxSetObjectIntParameter',objectHandle_,parameterID_,parameterValue_,operationMode_);
		end

		function [rtn ]= simxSetObjectOrientation(obj,objectHandle,relativeToObjectHandle,eulerAngles,operationMode)
			objectHandle_ = int32(objectHandle);
			relativeToObjectHandle_ = int32(relativeToObjectHandle);
			num_ele = numel(eulerAngles);
			if (num_ele < 3)
				error('Euler angles should have 3 values');
				return;
			else
			eulerAngles_ = libpointer('singlePtr',single(eulerAngles));
			operationMode_ = int32(operationMode);
		    
			[rtn ] = calllib(obj.libName,'simxSetObjectOrientation',objectHandle_,relativeToObjectHandle_,eulerAngles_,operationMode_);
			end
		end

		function [rtn] = simxSetObjectParent(obj,objectHandle,parentObject,keepInPlace,operationMode)
			objectHandle_ = int32(objectHandle);
			parentObject_ = int32(parentObject);
			keepInPlace_ = int8(keepInPlace);
			operationMode_ = int32(operationMode);

			[rtn ] = calllib(obj.libName,'simxSetObjectParent',objectHandle_ ,parentObject_,keepInPlace_,operationMode_);
		end

		function rtn = simxSetObjectPosition(obj,handle,rel_pos,position,option)
			if (numel(position) < 3)
				error('position should have 3 values');
				return;
			end

			handle_ = int32(handle);
			rel_pos_ = int32(rel_pos);
			option_ = int32(option);
			pos_ptr = libpointer('singlePtr',single(position));
		    
		   [rtn pos_ptr] = calllib(obj.libName,'simxSetObjectPosition',handle_,rel_pos_,pos_ptr,option_);
		end

		function [rtn] = simxSetObjectSelection(obj,objectHandles,operationMode)
			objectHandles_ = libpointer('int32Ptr',int32(objectHandles));
			objectCount = numel(objectHandles);
			operationMode_ = int32(operationMode);

			[rtn objectHandles_ ] = calllib(obj.libName,'simxSetObjectSelection',objectHandles_ ,objectCount,operationMode_);
		end

		function [rtn ]= simxSetSphericalJointMatrix(obj,jointHandle,matrix,operationMode)
			jointHandle_ = int32(jointHandle);
			num_ele = numel(matrix);
			if (num_ele < 12)
				error('matrix should have 12 values');
				return;
			else
				matrix_ = libpointer('singlePtr',single(matrix));
				operationMode_ = int32(operationMode);
		        
				[rtn signalName_ ] = calllib(obj.libName,'simxSetSphericalJointMatrix',jointHandle_,matrix_,operationMode_);
			end
		end

		function [rtn ]= simxSetStringSignal(obj,signalName,signalValue,operationMode)
			signalLength_ = int32(length(signalValue));
			signalName_ = libpointer('int8Ptr',[int8(signalName) 0]);
			signalValue_ = libpointer('int8Ptr',[int8(signalValue) 0]);
			operationMode_ = int32(operationMode);

			[rtn signalName_ signalValue_ ] = calllib(obj.libName,'simxSetStringSignal',signalName_,signalValue_,signalLength_ ,operationMode_);
		end

		function [rtn ] = simxSetUIButtonLabel(obj,uiHandle,uiButtonID,upStateLabel,downStateLabel,operationMode)
   			uiHandle_ = int32(uiHandle);
			operationMode_ = int32(operationMode);
   			uiButtonID_ = int32(uiButtonID);
			upStateLabel_ = libpointer('int8Ptr',int8([upStateLabel 0]));
			downStateLabel_ = libpointer('int8Ptr',int8([downStateLabel 0]));

			[rtn upStateLabel_ downStateLabel_] = calllib(obj.libName,'simxSetUIButtonLabel',uiHandle_,uiButtonID_,upStateLabel_,downStateLabel_,operationMode_);
		end

		function [rtn ] = simxSetUIButtonProperty(obj,uiHandle,uiButtonID,prop,operationMode)
			uiHandle_ = int32(uiHandle);
			operationMode_ = int32(operationMode);
			uiButtonID_ = int32(uiButtonID);
			prop_ = int32(prop);
		    
			[rtn ] = calllib(obj.libName,'simxSetUIButtonProperty',uiHandle_,uiButtonID_,prop_,operationMode_);
		end

		function [rtn] = simxSetUISlider (obj,uiHandle,uiButtonID,position,operationMode)
			uiHandle_ = int32(uiHandle);
			operationMode_ = int32(operationMode);
			uiButtonID_ = int32(uiButtonID);
			position_ = int32(position);
		    
			[rtn] = calllib(obj.libName,'simxSetUISlider',uiHandle_,uiButtonID_,position_,operationMode_)
		end

		function rtn = simxSetVisionSensorImage(obj,handle,image,buffsize,options,operationmode)
			handle_ = int32(handle);
			buffsize_ = int32(buffsize);
			options_ = int8(options);
			operationmode_ = int32(operationmode);

			[rtn image] = calllib(obj.libName,'simxSetVisionSensorImage',handle_,image,buffsize_,options_,operationmode_);
		end

		function rtn = simxSetVisionSensorImage2(obj,handle,image,operationmode)
			handle_ = int32(handle);
			[m n o] = size(image);
			buffsize_ = int32(m*n*o);
			if(o == 1)
				options_ = int8(1);
			else
				options_ = int8(0);
			end
			operationmode_ = int32(operationmode);
			imdata = zeros(1,buffsize_);
			imdata= cast(imdata,'uint8');

			for i = m:-1:1;
				count = (m-i)*n*o;
				for j = 1:o:n*o;
					for k=1:o;
						if(o==1)
							l=j;
						else
							l=int32(j/o) +1;
						end
						imdata(count+j+k-1) = image(i,l,k);
					end
				end
			end

			image_ = libpointer('int8Ptr',imdata);
		 
			[rtn image_] = calllib(obj.libName,'simxSetVisionSensorImage',handle_,image_,buffsize_,options_,operationmode_); 
		end

		function rtn = simxStartSimulation(obj,operationMode)
			operationMode_ = int32(operationMode);
		    
			rtn = calllib(obj.libName,'simxStartSimulation',operationMode_);
		end

		function rtn = simxStopSimulation(obj,operationMode)
			operationMode_ = int32(operationMode);
		    
			rtn = calllib(obj.libName,'simxStopSimulation',operationMode_);
		end

		function rtn = simxSynchronous(obj,enable)
			enable_ = int8(enable);
		    
			rtn = calllib(obj.libName,'simxSynchronous',enable_);
		end

		function rtn = simxPauseCommunication(obj,enable)
			enable_ = int8(enable);
		    
			rtn = calllib(obj.libName,'simxPauseCommunication',enable_);
		end

		function rtn = simxSynchronousTrigger(obj)
			rtn = calllib(obj.libName,'simxSynchronousTrigger');
		end

		function rtn = simxTransferFile(obj,filePathAndName,fileName_serverSide,timeOut,operationMode)
			filePathAndName_ = libpointer('int8Ptr',[int8(filePathAndName) 0]);
			fileName_serverSide_ = libpointer('int8Ptr',[int8(fileName_serverSide) 0]);
			timeOut_ = int32(timeOut);
			operationMode_ = int32(operationMode);

			[rtn filePathAndName_ fileName_serverSide_] = calllib(obj.libName,'simxTransferFile',filePathAndName_,fileName_serverSide_,timeOut_,operationMode_);
		end


    end   
end

