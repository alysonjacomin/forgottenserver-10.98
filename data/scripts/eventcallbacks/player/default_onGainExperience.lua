local soulCondition = Condition(CONDITION_SOUL, CONDITIONID_DEFAULT)
soulCondition:setTicks(4 * 60 * 1000)
soulCondition:setParameter(CONDITION_PARAM_SOULGAIN, 1)

local function useStamina(self)
	local staminaMinutes = self:getStamina()
	if staminaMinutes == 0 then
		return
	end

	local playerId = self:getId()
	if not nextUseStaminaTime[playerId] then
		nextUseStaminaTime[playerId] = 0
	end

	local currentTime = os.time()
	local timePassed = currentTime - nextUseStaminaTime[playerId]
	if timePassed <= 0 then
		return
	end

	if timePassed > 60 then
		if staminaMinutes > 2 then
			staminaMinutes = staminaMinutes - 2
		else
			staminaMinutes = 0
		end
		nextUseStaminaTime[playerId] = currentTime + 120
	else
		staminaMinutes = staminaMinutes - 1
		nextUseStaminaTime[playerId] = currentTime + 60
	end
	self:setStamina(staminaMinutes)
end

local default = Event()
 
function default.onGainExperience(self, source, exp, rawExp, sendText)
	if not source or source:isPlayer() then
		return exp
	end

	local level = self:getLevel()

	-- Soul regeneration
	local vocation = self:getVocation()
	if self:getSoul() < vocation:getMaxSoul() and exp >= level then
		soulCondition:setParameter(CONDITION_PARAM_SOULTICKS, vocation:getSoulGainTicks() * 1000)
		self:addCondition(soulCondition)
	end

	-- Apply experience stage multiplier
	exp = exp * Game.getExperienceStage(level)

	-- Stamina modifier
	if configManager.getBoolean(configKeys.STAMINA_SYSTEM) then
		useStamina(self)

		local staminaMinutes = self:getStamina()
		if staminaMinutes > 2400 and self:isPremium() then
			exp = exp * 1.5
		elseif staminaMinutes <= 840 then
			exp = exp * 0.5
		end
	end

	-- Apply low level bonus
	exp = exp * (1 + self:calculateLowLevelBonus(level) / 100)
	return exp
end

default:register()