function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end

	if param == "" then
		player:sendTextMessage(MESSAGE_STATUS_WARNING, "Command requires 1 parameter: /unban <player name>")
		return true
	end

	local resultId = db.storeQuery("SELECT `account_id`, `lastip` FROM `players` WHERE `name` = " .. db.escapeString(param))
	if not resultId then
		return true
	end

	local accountId = result.getNumber(resultId, "account_id")
	local lastIp = result.getString(resultId, "lastip")
	result.free(resultId)

	db.asyncQuery("DELETE FROM `account_bans` WHERE `account_id` = " .. db.escapeString(tostring(accountId)))
	db.asyncQuery("DELETE FROM `ip_bans` WHERE `ip` = " .. db.escapeString(lastIp))

	player:sendTextMessage(MESSAGE_EVENT_ADVANCE, string.format("%s has been unbanned.", param))

	return true
end
