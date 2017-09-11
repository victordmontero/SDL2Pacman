premake.modules.vscode = {}
local m = premake.modules.vscode
local p = premake

newaction {
	trigger         = "vscode",
	shortname       = "Visual Studio Code",
	description     = "Generate tasks.json",

	valid_kinds     = { "ConsoleApp", "StaticLib", "SharedLib" },

	valid_languages = { "C", "C++" },

    onWorkspace = function(wks)
        local cwd = os.getcwd()
        -- local dir = cwd.."/"..prj.name.."/.vscode/tasks.json"
        local dir = string.format("%s/.vscode/tasks.json",cwd,wks.name)
		p.generate(wks, dir, m.generateWorkspace)
	end,
	onProject = function(prj)
	end,
	onCleanWorkspace = function(wks)
        local dir = string.format("%s/.vscode/tasks.json",cwd,wks.name)
		p.clean.file(wks, dir)
	end,
	onCleanProject = function(prj)
    local dir = string.format("%s/%s/.vscode/tasks.json",cwd,prj.name)
		p.clean.file(prj, dir)
	end,
	onCleanTarget = function(prj)
		p.modules.vscode.cleanTarget(prj)
	end,
	onEnd = function()
		print("Tasks.json generation complete")
		p.action.call("gmake")
	end
}

function m.generateWorkspace( wks )
    p.w(string.format("//%s Tasks.json",wks.name))
	createTaskStruct(wks)
end

function m.generateProject( prj )
    p.w(string.format("//%s Tasks.json",prj.name))
	createTaskStruct(prj)
end

function createTaskStruct(thing)
    p.push('{')
	p.w("// Generated by Premake5")
	p.w('"version":"2.0.0",')
	p.push('"tasks": [')
	generateTasks(thing)
	p.pop("]")
	p.pop("}")
end

function generateTasks( thing )
	local platforms = thing.platforms
	local configs = thing.configurations

	for prj in p.workspace.eachproject(thing) do
		for x,y in pairs(configs) do
			for a,b in pairs(platforms) do
				if type(a) ~= "number" and type(x) ~= "number" then
					local taskName = string.format("%s_%s %s",string.lower(y),string.lower(b),prj.name)
					local command = ""
					if string.lower(b) == "linux" then
						command = string.format("make config=%s",taskName)
					else
						command = string.format("mingw32-make config=%s",taskName)
					end
					generateTask("Build ".. taskName,"shell",command)
				end
			end
		end
	end

	generateTask("Clean","shell","mingw32-make clean")

end

function generateTask( taskName,type,command )
	p.push("{")
	p.w(string.format('"taskName":"%s",',taskName))
	p.w(string.format( '"type":"%s",',type))
	p.w(string.format('"command":"%s"',command))
	p.pop("},")
end

return m