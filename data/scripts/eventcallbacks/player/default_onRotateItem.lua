local event = Event()

event.onRotateItem = function(self, item)
	local newId = item:getType():getRotateTo()
	if newId ~= 0 then
		item:transform(newId)
	end
end
 
event:register()