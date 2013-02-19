-- this add-on simply adds an alternative UI that allows to start/stop/pause a simulation. This is not very useful,
-- but illustrates how easily V-REP can be customized using add-ons
execMode=...
if (execMode==0) then
	uiHandles=simLoadUI('addOnDemoUi.ttb')
	if (#uiHandles==1) then
		simSetUIProperty(uiHandles[1],simGetUIProperty(uiHandles[1])+sim_ui_property_pauseactive+sim_ui_property_systemblock)
		uiHandle=uiHandles[1]
		defButProp=simGetUIButtonProperty(uiHandle,0)
		defUiProp=simGetUIProperty(uiHandle)
	else
		simDisplayDialog('Error','"addOnDemoUi.ttb" was not found!',sim_dlgstyle_ok,false,nil,{0.8,0,0,0,0,0},{0.5,0,0,1,1,1})
	end
end

if (uiHandle) then
	editModeType=simGetIntegerParameter(sim_intparam_edit_mode_type)
	if (editModeType==0)and(execMode==1) then
		simSetUIProperty(uiHandle,defUiProp)
		simState=simGetSimulationState()
		buttonID=simGetUIEventButton(uiHandle)
		if (buttonID==0) then
			-- start was clicked
			if (simBoolAnd16(simState,sim_simulation_advancing)==0) then
				simStartSimulation()
			end
		end
		if (buttonID==1) then
			-- pause was clicked
			if (simBoolAnd16(simState,sim_simulation_advancing)~=0) then
				simPauseSimulation()
			end
		end
		if (buttonID==2) then
			-- stop was clicked
			if (simState~=sim_simulation_stopped) then
				simStopSimulation()
			end
		end
		if (simBoolAnd16(simState,sim_simulation_advancing)~=0) then
			-- advancing
			simSetUIButtonProperty(uiHandle,0,defButProp+sim_buttonproperty_isdown-sim_buttonproperty_enabled)
			simSetUIButtonProperty(uiHandle,1,defButProp)
			simSetUIButtonProperty(uiHandle,2,defButProp)
		else
			if (simState==sim_simulation_stopped) then
				-- stopped
				simSetUIButtonProperty(uiHandle,0,defButProp)
				simSetUIButtonProperty(uiHandle,1,defButProp-sim_buttonproperty_enabled)
				simSetUIButtonProperty(uiHandle,2,defButProp-sim_buttonproperty_enabled)
			else
				-- paused
				simSetUIButtonProperty(uiHandle,0,defButProp)
				simSetUIButtonProperty(uiHandle,1,defButProp+sim_buttonproperty_isdown-sim_buttonproperty_enabled)
				simSetUIButtonProperty(uiHandle,2,defButProp)
			end
		end
	else
		simSetUIProperty(uiHandle,defUiProp-sim_ui_property_visible) -- hide the UI
	end
end
