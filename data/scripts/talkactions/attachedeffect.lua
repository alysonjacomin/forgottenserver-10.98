local mehah = {
    talkactions = {
        attacheffect = "!attacheffect",
        detachEffect = "!detacheffect",
        playerSetShader = "!playerSetShader",
        itemSetShader = "!itemSetShader",
        mapShader = "!mapShader"
    },
}

local events = {}

local function processCommand(player, words, param, type, action)
    if not player:getGroup():getAccess() or player:getAccountType() < ACCOUNT_TYPE_GOD then
        player:sendCancelMessage("No tienes acceso a este comando.")
        return false
    end

    local params, arg
    if param:find("\"") then
        params = { param:match("\"(.+)\",*(.*)") }
        arg = params[1]
        print(params)
        print(arg)
        pdump(params)
    else
        params = param:split(", ")
        arg = params[1]
        print("2",params)
        print("2",arg)
    end

    if not arg then
        player:sendCancelMessage("Parámetro inválido. Por favor proporciona un argumento válido.")
        return false
    end

    local creature
    if params[2] and params[2] ~= ""  then
        creature = Player(params[2])
        if not creature then
            player:sendCancelMessage("El nombre del jugador proporcionado no es válido.")
            return false
        end
    else
        creature = player
    end

    action(creature, arg)
    return false
end

local attachEffect = TalkAction(mehah.talkactions.attacheffect)
function attachEffect.onSay(player, words, param, type)
    return processCommand(player, words, param, type, function(creature, effect)
        creature:attachEffectById(tonumber(effect), false)
    end)
end
table.insert(events, attachEffect)

local detachEffect = TalkAction(mehah.talkactions.detachEffect)
function detachEffect.onSay(player, words, param, type)
    return processCommand(player, words, param, type, function(creature, effect)
        creature:detachEffectById(tonumber(effect))
    end)
end
table.insert(events, detachEffect)

local setShader = TalkAction(mehah.talkactions.playerSetShader)
function setShader.onSay(player, words, param, type)
    return processCommand(player, words, param, type, function(creature, shader)
        creature:setShader(shader)
    end)
end
table.insert(events, setShader)

local mapShader = TalkAction(mehah.talkactions.mapShader)
function mapShader.onSay(player, words, param, type)
    return processCommand(player, words, param, type, function(creature, shader)
        if creature:getMapShader() ~= shader then
            creature:setMapShader(shader, true)
        end
    end)
end
table.insert(events, mapShader)

for _, event in ipairs(events) do
    event:accountType(ACCOUNT_TYPE_GOD)
    event:access(true)
    event:separator(" ")
    event:register()
end